##
# String
#
# ISO 15.2.10
class String
  # ISO 15.2.10.3
  include Comparable

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
