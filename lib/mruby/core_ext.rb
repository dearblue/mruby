autoload :Pathname, 'pathname'

class Object
  class << self
    def attr_block(*syms)
      syms.flatten.each do |sym|
        class_eval "def #{sym}(&block);block.call(@#{sym}) if block_given?;@#{sym};end"
      end
    end
  end

  def fileset_list_under(basedir)
    [self].fileset_list_under(basedir)
  end

  def fileset_make_under(*dirs, prefix: nil)
    [self].fileset_make_under(*dirs, prefix: prefix)
  end
end

class Array
  def fileset_list_under(basedir)
    basedir = Pathname.new(basedir)
    alist = []
    _fileset_traverse_under(basedir, nil, nil, nil, {}) do |path, entity|
      alist << entity if entity.respond_to?(:to_path)
      nil
    end
    alist
  end

  def fileset_make_under(basedir, *dirs, prefix: nil)
    basedir = Pathname.new(basedir)
    prefix = "#{prefix}:" if prefix
    alist = {}
    _fileset_traverse_under(basedir, dirs, prefix, alist, {}) do |path, entity|
      case entity
      when nil
        nil
      when String
        entity
      when Proc, Method
        entity.call
      else # File, Pathname, StringIO, ...
        entity.read
      end
    end
    alist.empty? ? nil : alist
  end

  def _fileset_traverse_under(basedir, dirs, prefix, alist, recursive_list, &block)
    each do |entry|
      case entry
      when nil
      when Array
        unless recursive_list[entry.object_id]
          recursive_list[object_id] = true
          ex = entry._fileset_traverse_under(basedir, dirs, prefix, recursive_list, &block)
          alist.merge!(ex) { |key, *| _fileset_traverse_error basedir, key } if ex
        end
      when Hash
        entry.each do |path, entity|
          case entity
          when Pathname
            _fileset_traverse_add(basedir, dirs, prefix, alist, basedir + path, basedir + entity, &block)
          else
            _fileset_traverse_add(basedir, dirs, prefix, alist, basedir + path, entity, &block)
          end
        end
      when String, Pathname
        _fileset_traverse_add(basedir, dirs, prefix, alist, basedir + entry, basedir + entry, &block)
      else
        _fileset_traverse_add(basedir, dirs, prefix, alist, basedir + entry, entry, &block)
      end
    end
  end

  def _fileset_traverse_add(basedir, dirs, prefix, alist, path, entity, &block)
    name = path.to_s.relative_path_under(basedir, *dirs)
    entity = String(yield path, entity)
    unless alist.nil? || entity.empty?
      key = "#{prefix}#{name}"
      _fileset_traverse_error basedir, key if alist.key?(key)
      alist[key] = entity
    end
  end

  def _fileset_traverse_error(basedir, key)
    raise "conflict file name - #{key} for #{basedir}"
  end
end

class String
  def relative_path_from(dir)
    Pathname.new(File.expand_path(self)).relative_path_from(Pathname.new(File.expand_path(dir))).to_s
  end

  def relative_path
    relative_path_from(Dir.pwd)
  end

  def relative_path_under(*dirs)
    dirs.each do |dir|
      return relative_path_from dir if start_with? File.join(dir, "/")
    end

    self
  end

  def remove_leading_parents
    Pathname.new(".#{Pathname.new("/#{self}").cleanpath}").cleanpath.to_s
  end
end

class File
  def File.extract(path, pattern, *args, mode: "rt", **opts)
    # NOTE: cygwin においては、読み込みに明示的なテキストモード指定が必要
    src = File.read(path, *args, mode: mode, **opts)
    src.slice(pattern) or raise "pattern mismatch - #{path}"
  end
end

def install_D(src, dst)
  _pp "INSTALL", src.relative_path, dst.relative_path
  rm_f dst
  mkdir_p File.dirname(dst)
  cp src, dst
end

def _pp(cmd, src, tgt=nil, indent: nil)
  return if Rake.application.options.silent

  width = 5
  template = indent ? "%#{width * indent}s %s %s" : "%-#{width}s %s %s"
  puts template % [cmd, src, tgt ? "-> #{tgt}" : nil]
end
