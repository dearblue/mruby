# NOTE: Currently, this configuration file does not support VisualC++!
#       Your help is needed!

require "mruby/source"

mrbcfile = nil
MRuby::Build.new("host/mrbc") do |conf|
  conf.toolchain
  conf.gem core: "mruby-bin-mrbc"
  conf.disable_presym
  conf.enable_debug

  mrbcfile = File.join(conf.build_dir, "bin/mrbc")
end

MRuby::Build.new do |conf|
  # load specific toolchain settings
  conf.toolchain

  conf.mrbcfile = mrbcfile

  # include the GEM box
  conf.gembox 'default'

  # C compiler settings
  conf.compilers.each do |cc|
    cc.flags << '-fPIC'
  end

  vermap = File.join(conf.build_dir, "libmruby.map")
  conf.archiver do |archiver|
    archiver.command = cc.command
    ## TODO: vermap を直接埋め込むのではなくてパラメータで指定する
    archiver.archive_options = "-shared -o %{outfile} %{objs} -Wl,--version-script=#{vermap}"
  end

  # file extensions
  conf.exts do |exts|
    exts.library = '.so'
  end

  # file separator
  # conf.file_separator = '/'

  # change library directory name from the default "lib" if necessary
  # conf.libdir_name = 'lib64'

  # バージョンスクリプトファイルを別に用意している場合はこのタスクは不要です。
  file File.join(conf.build_dir, "lib", conf.libfile("libmruby")) => vermap do |t|
    t.prerequisites.delete vermap
  end
  file File.join(conf.build_dir, "lib", conf.libfile("libmruby_core")) => vermap do |t|
    t.prerequisites.delete vermap
  end
  task vermap do |t|
    sig = "MRUBY_#{MRuby::Source::MRUBY_RELEASE_NO}\n"
    if File.file?(vermap) &&
        (ts = File.mtime(vermap)) > File.mtime(__FILE__) &&
        File.read(vermap, sig.size) == sig
      t.define_singleton_method(:timestamp, -> { ts })
    else
      _pp "GEN", vermap.relative_path
      mkdir_p File.dirname(vermap)
      File.write(vermap, <<~VERMAP)
        #{sig}{
          global:
            *;
          local:
            *;
        };
      VERMAP
    end
  end

  conf.test_runner do |runner|
    #runner.command = "valgrind"  # 必要であれば。ただし bintest と組み合わせられない。
    runner.env["LD_LIBRARY_PATH"] = File.join(conf.build_dir, "lib")
  end

  conf.linker do |linker|
    linker.flags << "-Wl,-rpath,#{conf.install_prefix}/lib"
  end

  # enable this if better compatibility with C++ is desired
  #conf.enable_cxx_exception

  # Turn on `enable_debug` for better debugging
  conf.enable_debug
  conf.enable_bintest
  conf.enable_test
end
