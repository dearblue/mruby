##
# String
#
# ISO 15.2.10
class String
  # ISO 15.2.10.3
  include Comparable

  def __parse_aref(args)
    off1 = args[0]
    regs = []
    case args.size
    when 1
      off1 = off1..off1 if off1.kind_of?(Numeric)
      unless off1.respond_to?(:__str_index_in)
        raise TypeError, "expect String, Regexp or Range"
      end
      regs = off1.__str_index_in(self, 0, regs)
    when 2
      len = args[1]
      case off1
      when Numeric
        len = len.__to_int
        return nil if len < 0
        off1 = off1.to_i
        if len > 0
          off2 = off1 + len
          if off2 == 0
            off2 = off1 + len - 1
            regs = (off1 .. off2).__str_index_in(self, 0, regs)
          else
            regs = (off1 ... off2).__str_index_in(self, 0, regs)
          end
        else
          regs = (off1 .. off1).__str_index_in(self, 0, regs)
          regs[1] = regs[0] if regs
        end
      else
        unless off1.respond_to?(:__str_index_in) && !off1.kind_of?(String) && !off1.kind_of?(Range)
          raise TypeError, "expect Integer or Regexp"
        end
        regs = off1.__str_index_in(self, len, regs)
      end
    else
      raise ArgumentError, "wrong number of arguments"
    end

    regs
  end

  ##
  # call-seq:
  #   str[fixnum]                 => fixnum or nil
  #   str[fixnum, fixnum]         => new_str or nil
  #   str[range]                  => new_str or nil
  #   str[other_str]              => new_str or nil
  #   str.slice(fixnum)           => fixnum or nil
  #   str.slice(fixnum, fixnum)   => new_str or nil
  #   str.slice(range)            => new_str or nil
  #   str.slice(other_str)        => new_str or nil
  #
  # Element Reference---If passed a single <code>Fixnum</code>, returns the code
  # of the character at that position. If passed two <code>Fixnum</code>
  # objects, returns a substring starting at the offset given by the first, and
  # a length given by the second. If given a range, a substring containing
  # characters at offsets given by the range is returned. In all three cases, if
  # an offset is negative, it is counted from the end of +str+. Returns
  # <code>nil</code> if the initial offset falls outside the string, the length
  # is negative, or the beginning of the range is greater than the end.
  #
  # If a <code>String</code> is given, that string is returned if it occurs in
  # +str+. In both cases, <code>nil</code> is returned if there is no
  # match.
  #
  #   a = "hello there"
  #   a[1]                   #=> 101(1.8.7) "e"(1.9.2)
  #   a[1.1]                 #=>            "e"(1.9.2)
  #   a[1,3]                 #=> "ell"
  #   a[1..3]                #=> "ell"
  #   a[-3,2]                #=> "er"
  #   a[-4..-2]              #=> "her"
  #   a[12..-1]              #=> nil
  #   a[-2..-4]              #=> ""
  #   a["lo"]                #=> "lo"
  #   a["bye"]               #=> nil
  #
  # ISO 15.2.10.5.6
  def [](*args)
    (off1, off2) = __parse_aref(args)
    return nil unless off1
    byteslice(off1, off2 - off1)
  end

  # ISO 15.2.10.5.34
  alias slice []

  ##
  # call-seq:
  #   str[fixnum] = replace
  #   str[fixnum, fixnum] = replace
  #   str[range] = replace
  #   str[other_str] = replace
  #
  # Modify <code>self</code> by replacing the content of <code>self</code>.
  # The portion of the string affected is determined using the same criteria as <code>String#[]</code>.
  def []=(*args, replace)
    replace.__to_str
    (off1, off2) = __parse_aref(args)
    raise IndexError, "index #{args.size > 1 ? args.inspect : args[0]} out of string" unless off1
    __bytereplace(off1, off2, replace)
    self
  end

  ##
  # Calls the given block for each line
  # and pass the respective line.
  #
  # ISO 15.2.10.5.15
  def each_line(separator = "\n", &block)
    return to_enum(:each_line, separator) unless block

    if separator.nil?
      block.call(self)
      return self
    end

    case
    when separator == ""
      paragraph_mode = true
      separator = "\n\n"
    when separator.respond_to?(:__str_index_in)
      paragraph_mode = false
    else
      raise TypeError, "expect String or Regexp"
    end

    start = 0
    string = dup
    self_len = bytesize
    should_yield_subclass_instances = self.class != String
    regs = []

    while true
      if separator.__str_index_in(string, start, regs)
        pointer = regs[1]
        pointer += 1 while paragraph_mode && string.byteslice(pointer, 1) == "\n"
      else
        break unless start > 0 && start < self_len
        pointer = self_len
      end
      if should_yield_subclass_instances
        block.call(self.class.new(string.byteslice(start, pointer - start)))
      else
        block.call(string.byteslice(start, pointer - start))
      end
      start = pointer
    end
    self
  end

  # private method for gsub/sub
  def __sub_replace(pre, m, post)
    s = ""
    i = 0
    while j = index("\\", i)
      break if j == length-1
      t = case self[j+1]
          when "\\"
            "\\"
          when "`"
            pre
          when "&", "0"
            m
          when "'"
            post
          when "1", "2", "3", "4", "5", "6", "7", "8", "9"
            ""
          else
            self[j, 2]
          end
      s += self[i, j-i] + t
      i = j + 2
    end
    s + self[i, length-i]
  end

  ##
  # Replace all matches of +pattern+ with +replacement+.
  # Call block (if given) for each match and replace
  # +pattern+ with the value of the block. Return the
  # final value.
  #
  # ISO 15.2.10.5.18
  def gsub(*args, &block)
    return to_enum(:gsub, *args) if args.length == 1 && !block
    raise ArgumentError, "wrong number of arguments" unless (1..2).include?(args.length)

    pattern, replace = *args
    plen = pattern.length
    if args.length == 2 && block
      block = nil
    end
    if !replace.nil? || !block
      replace.__to_str
    end
    offset = 0
    result = []
    while found = index(pattern, offset)
      result << self[offset, found - offset]
      offset = found + plen
      result << if block
        block.call(pattern).to_s
      else
        replace.__sub_replace(self[0, found], pattern, self[offset..-1] || "")
      end
      if plen == 0
        result << self[offset, 1]
        offset += 1
      end
    end
    result << self[offset..-1] if offset < length
    result.join
  end

  ##
  # Replace all matches of +pattern+ with +replacement+.
  # Call block (if given) for each match and replace
  # +pattern+ with the value of the block. Modify
  # +self+ with the final value.
  #
  # ISO 15.2.10.5.19
  def gsub!(*args, &block)
    raise FrozenError, "can't modify frozen String" if frozen?
    return to_enum(:gsub!, *args) if args.length == 1 && !block
    str = self.gsub(*args, &block)
    return nil unless self.index(args[0])
    self.replace(str)
  end

#  ##
#  # Calls the given block for each match of +pattern+
#  # If no block is given return an array with all
#  # matches of +pattern+.
#  #
#  # ISO 15.2.10.5.32
#  def scan(pattern, &block)
#    # TODO: String#scan is not implemented yet
#  end

  ##
  # call-seq:
  #   str.split(separator=nil, [limit])   => anArray
  #
  # Divides +str+ into substrings based on a delimiter, returning an array
  # of these substrings.
  #
  # If +separator+ is a <code>String</code>, then its contents are used as
  # the delimiter when splitting +str+. If +separator+ is a single
  # space, +str+ is split on whitespace, with leading whitespace and runs
  # of contiguous whitespace characters ignored.
  #
  # If +separator+ is omitted or <code>nil</code> (which is the default),
  # +str+ is split on whitespace as if ' ' were specified.
  #
  # If the +limit+ parameter is omitted, trailing null fields are
  # suppressed. If +limit+ is a positive number, at most that number of
  # fields will be returned (if +limit+ is <code>1</code>, the entire
  # string is returned as the only entry in an array). If negative, there is no
  # limit to the number of fields returned, and trailing null fields are not
  # suppressed.
  #
  #   " now's  the time".split        #=> ["now's", "the", "time"]
  #   " now's  the time".split(' ')   #=> ["now's", "the", "time"]
  #
  #   "mellow yellow".split("ello")   #=> ["m", "w y", "w"]
  #   "1,2,,3,4,,".split(',')         #=> ["1", "2", "", "3", "4"]
  #   "1,2,,3,4,,".split(',', 4)      #=> ["1", "2", "", "3,4,,"]
  #   "1,2,,3,4,,".split(',', -4)     #=> ["1", "2", "", "3", "4", "", ""]
  #
  # ISO 15.2.10.5.35
  def split(*args, &block)
    unless block
      result = []
      split(*args) { |sub| result << sub }
      return result
    end

    pat = args[0]
    case args.size
    when 0, 1
      limit = nil
    when 2
      limit = args[1].__to_int
    else
      raise ArgumentError, "wrong number of arguments"
    end

    if pat.nil? || pat == " "
      pat = nil
    else
      unless pat.respond_to?(:__str_index_in)
        raise TypeError, "expected String or Regexp"
      end
    end

    if limit == 1
      yield self if size > 0
      return self
    end

    beg = 0
    term = bytesize
    blanks = 0

    if pat
      regs = []
      while true
        unless regs = pat.__str_index_in(self, beg, regs)
          break unless term > 0 && beg < term
          regs = [term, term]
        end
        (pre, post) = regs
        if beg == pre
          blanks += 1
        else
          blanks.times { yield "" }
          blanks = 0
          yield byteslice(beg, pre - beg)
        end

        beg = post
        if limit && limit > 1
          limit -= 1
          break unless limit > 1
        end

        blanks += 1 if (pre != post || pat == "") && post == term
      end
    else
      while true
        unless (pre = __skip_whitespace(beg)) && (post = __search_whitespace(pre))
          beg = term
          yield "" if limit
          break
        end
        yield byteslice(pre, post - pre)

        beg = post
        if limit && limit > 1
          limit -= 1
          unless limit > 1
            beg = __skip_whitespace(beg)
            break
          end
        end
      end
    end

    if limit
      blanks.times { yield "" }
      yield byteslice(beg, term - beg) if beg && beg < term
    end

    self
  end

  ##
  # Replace only the first match of +pattern+ with
  # +replacement+. Call block (if given) for each
  # match and replace +pattern+ with the value of the
  # block. Return the final value.
  #
  # ISO 15.2.10.5.36
  def sub(*args, &block)
    unless (1..2).include?(args.length)
      raise ArgumentError, "wrong number of arguments (given #{args.length}, expected 2)"
    end

    pattern, replace = *args
    pattern.__to_str
    if args.length == 2 && block
      block = nil
    end
    unless block
      replace.__to_str
    end
    result = []
    this = dup
    found = index(pattern)
    return this unless found
    result << this[0, found]
    offset = found + pattern.length
    result << if block
      block.call(pattern).to_s
    else
      replace.__sub_replace(this[0, found], pattern, this[offset..-1] || "")
    end
    result << this[offset..-1] if offset < length
    result.join
  end

  ##
  # Replace only the first match of +pattern+ with
  # +replacement+. Call block (if given) for each
  # match and replace +pattern+ with the value of the
  # block. Modify +self+ with the final value.
  #
  # ISO 15.2.10.5.37
  def sub!(*args, &block)
    raise FrozenError, "can't modify frozen String" if frozen?
    str = self.sub(*args, &block)
    return nil unless self.index(args[0])
    self.replace(str)
  end

  ##
  # Call the given block for each byte of +self+.
  def each_byte(&block)
    return to_enum(:each_byte, &block) unless block
    bytes = self.bytes
    pos = 0
    while pos < bytes.size
      block.call(bytes[pos])
      pos += 1
    end
    self
  end

  # those two methods requires Regexp that is optional in mruby
  ##
  # ISO 15.2.10.5.3
  #def =~(re)
  # re =~ self
  #end

  ##
  # ISO 15.2.10.5.27
  #def match(re, &block)
  #  re.match(self, &block)
  #end
end
