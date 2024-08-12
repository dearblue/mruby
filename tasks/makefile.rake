# NOTE: The policy is to avoid proprietary extensions that BSD, GNU and others have.

desc "generate Makefile file suite for 'host' build target"
task :makefile => "makefile:suite:host"

using Module.new {
  refine Object do
    def file_copy_task(src, dest, headup: nil)
      unless Rake::Task.task_defined? dest
        file dest => src do |t|
          #_pp "COPY", src.relative_path, dest.relative_path
          mkdir_p File.dirname(dest)
          cp src, dest
        end
      end

      task headup => dest if headup
    end

    def stop_watch
      sw = Object.new
      start = wrap = Time.now.to_f
      sw.define_singleton_method :wrap, &-> {
        w = Time.now.to_f
        $stderr.puts %(%7.3f: (%+7.3f) %s\n) % [w - start, w - wrap, *caller(1, 1)]
        wrap = w
      }

      yield sw

      w = Time.now.to_f
      if start == wrap
        $stderr.puts %(%7.3f: %s\n) % [w - start, *caller(1, 1)]
      else
        $stderr.puts %(%7.3f: (%+7.3f) %s\n) % [w - start, w - wrap, *caller(1, 1)]
      end

      nil
    end
  end

  refine String do
    def glob_files(pat, **opts, &block)
      base = self.gsub(/[\[\{\*\?\\]/) { |e| "\\#{e}" }
      pat.map! { |e| File.join(base, e) } if pat.kind_of? Array
      list = Dir.glob(pat, **opts)
      list.uniq!
      list.each(&block) if block
      list
    end

    def to_make_echo(escape: true)
      mesg = self
      mesg = mesg.gsub("$", "$$") if escape
      mesg = mesg.split("\n").map { |mesg| "@ ${ECHO} #{mesg.inspect}" }.join("\n\t")
      mesg
    end
  end

  refine MRuby.singleton_class do
    def each_distribution_file(&block)
      return to_enum(__method__) unless block

      MRUBY_ROOT.glob_files(%w(AUTHORS* LEGAL* LICENSE* README* *.md doc/**/* include/**/* src/**/*)) do |path|
        yield path if File.file? path
      end
    end
  end

  refine MRuby::Gem::Specification do
    # gem 作者はビルドするためファイルが外部に出力されるためのファイル群を報告できるようにこのメソッドをオーバーライドできます。
    def each_distribution_file(&block)
      return to_enum(__method__) unless block

      # prepare_distribution_files # file タスクで依存関係を辿ることで解決したほうがいいかもしれない

      self.dir.glob_files(%w(AUTHORS* LEGAL* LICENSE* README* *.md COPYING* mrbgem.rake {doc,include,src,core,tools}/**/*)) do |path|
        yield path if File.file? path
      end

      self
    end

    def prepare_distribution_file(path, &block)
      file path => File.join(self.dir, "mrbgem.rake"), &block

      self
    end
  end
}

MRuby.each_target do |build|
  next if build.internal?

  #
  # TODO: 利用者定義のコンパイラ (rustc など) への対応を行う。
  # コンパイルだけですむように、事前に必要なバインディングのためのファイルを生成する必要がある。
  # そのためのフックメソッドや依存タスクを定義する。
  #
  # TODO: enable_cxx_exception や enable_cxx_abi によって生成された .cxx ファイルは本体への絶対パスを含んでいるため、どうにかする必要がある。
  # 出力は同じディレクトリになるから、相対ディレクトリ指定が出来る。
  # どうやって書き換える？汎用的なフックを実現できるか？
  #
  # TODO: README2.md みたいな形で注意点をまとめたほうがいいか？
  # 好ましくないストーリーの一つは、make の実行時に gems を追加したり取り除いたりできないため、mruby の柔軟性に疑問を持たれること。
  #
  # TODO: mrbgems のそれぞれの URL も記載するほうが良いかも？
  # gems はクローンしたファイル群をコピーするため、git の全設定が失われる。
  # URL も記載する場合は gem.homepage がある。
  #
  # TODO: 現状では mruby-bin-mrbc は libmruby_core.a とリンクする必要があるため、特別な配慮を行っている。
  # 汎用的な仕組みを導入して置き換える必要がある。
  #
  # TODO: 外部ライブラリを検出したりビルド呼び出したりする gems への対応を行う。
  # https://github.com/dearblue/mruby-buildconf を元にすればどうにかなりそうか？
  #
  # TODO: CMakeList.txt 生成タスクを書く。
  # また、他のビルドシステム定義ファイルを利用者が追加しやすくするための汎用フレームワークがあるといいかもしれない。
  #
  # TODO: いくつかの部分に置いて `rake install` タスクと共通化が出来ると思われる。
  # ヘッダファイルのコピーだとか 生成した Makefile の `install` タスクだとか？
  #
  # TODO: mrbgems/mruby-bin-config はビルド時に Ruby コードによって実行ファイルを作成するため、対応できない。
  # 生成するためのシェルスクリプト (あるいはバッチファイル) を書くか、C で再実装する必要がある。
  #
  # TODO: mruby プロジェクトで makefile 版のソースコードパッケージを配布することも有意義かもしれない。
  #
  # TODO: build_config/host-shared.rb は大丈夫か？
  #
  # TODO: https://github.com/dearblue/mruby-gemcut は大丈夫か？
  #
  # TODO: https://github.com/suetanvil/mruby-bin-monolith は大丈夫か？
  #
  # TODO: https://github.com/mattn/mruby-onig-regexp は大丈夫か？
  #
  # TODO: https://github.com/dearblue/mruby-stacktrace は大丈夫か？
  #
  # TODO: git archive で出力した mruby のソースコードから rake makefile しても大丈夫か？
  #

  headup = "makefile:suite:#{build.name}"
  prefix = File.join(build.build_dir, "makefile/mruby-#{MRuby::Source::MRUBY_VERSION}")

  task headup => File.join(prefix, "Makefile")

  task "makefile:hook:#{build.name}"

  file File.join(prefix, "Makefile") => [__FILE__, MRUBY_CONFIG] do |t|
    _pp "GEN", t.name.relative_path

    gemsinfo = ""
    if build.gems.empty?
      gemsinfo << " (EMPTY)"
    else
      build.gems.sort_by { |g| g.name }.each { |g| gemsinfo << "\n  %-20s  by %s" % [g.name, Array(g.authors).flatten.join(", ")] }
    end

    srcdir_map = { MRUBY_ROOT => "${SRCDIR}", build.build_dir => "${SRCDIR}" }
    workdir_map = { MRUBY_ROOT => "${WORKDIR}", build.build_dir => "${WORKDIR}" }
    cflags = build.cc.flags.flatten.join(" ")
    ldflags = build.linker.flags.join(" ")
    defines = [*build.defines, *build.cc.defines].flatten.uniq.map { |e| "-D#{e}" }.join(" ")
    include_paths = build.cc.include_paths.map { |e| "-I#{e.replace_prefix_by(srcdir_map)}" }.uniq.join(" ")
    library_paths = (build.linker.library_paths.map { |e| "-L#{e.replace_prefix_by(workdir_map)}" } << "-L${libdir}").join(" ")
    libraries = build.linker.libraries.map { |e| "-l#{e}" }.join(" ")
    libmruby_core_objs = build.libmruby_core_objs.flatten.uniq.sort
    libmruby_objs = build.libmruby_objs.flatten.uniq.sort
    libmruby_core_objs_list = libmruby_core_objs.replace_prefix_by(workdir_map).join(" \\\n\t")
    libmruby_objs_list = libmruby_objs.replace_prefix_by(workdir_map).join(" \\\n\t")
    libmruby_core_static = build.libmruby_core_static.replace_prefix_by(workdir_map)
    libmruby_static = build.libmruby_static.replace_prefix_by(workdir_map)
    products0 = build.gems.each_with_object([]) { |g, a| a << g.bins }.flatten
    products0 << "mrbc" if build.gems.find { |g| g.name == "mruby-bin-mrbc" }
    products0.uniq!
    products0.sort!
    products = products0.map { |e| "${WORKDIR}/bin/#{e}" }.join(" \\\n\t")

    incdir = build.gems.map { |g| g.export_include_paths.replace_prefix_by({ g.dir => "${SRCDIR}/mrbgems/#{g.name}" }.merge(srcdir_map)) }.flatten.uniq.map { |e| %(-I#{e.inspect}) }.join(" ")

    mkdir_p File.dirname(t.name) unless File.directory? File.dirname(t.name)
    File.binwrite t.name, <<~MAKEFILE.gsub(/^  /, "\t")
      #
      # This file is automatically generated by `rake #{headup}`
      # All direct changes to this file will be lost.
      #

      SRCDIR = .
      WORKDIR = .

      V = 0
      ECHO = echo
      MKDIR_P = mkdir -p
      RM_RF = rm -rf

      CC = #{build.cc.command}
      CXX = c++
      AS = as
      LD = #{build.linker.command}
      AR = #{build.archiver.command}
      CFLAGS = #{cflags}
      LDFLAGS = #{ldflags}
      defines = #{defines}
      include_paths = #{include_paths}
      library_paths = #{library_paths}
      libraries = #{libraries}
      bindir = ${WORKDIR}/bin
      docdir = ${WORKDIR}/doc
      incdir = ${WORKDIR}/include
      libdir = ${WORKDIR}/lib
      mandir = ${WORKDIR}/man
      objext = .o
      execext =

      PRODUCTS = \\
        ${libmruby_core_static} \\
        ${libmruby_static} \\
        #{products}
      libmruby_core_static = ${libdir}/libmruby_core#{build.exts.library}
      libmruby_static = ${libdir}/libmruby#{build.exts.library}
      libmruby_core_objs = \\\n\t#{libmruby_core_objs_list}
      libmruby_objs = \\\n\t#{libmruby_objs_list}

      PP0 =
      PP1 = > /dev/null
      PP = ${PP${V}}
      PPQ0 = @
      PPQ1 =
      PPQ = ${PPQ${V}}

      .PHONY: all clean install help about
      all: ${PRODUCTS}
      clean:
        @- ${ECHO} "clean working object files" ${PP}
        ${PPQ}- ${RM_RF} ${libmruby_core_objs} ${libmruby_objs}
      install:  # TODO

      ${libmruby_core_static}: ${libmruby_core_objs}
        @- ${MKDIR_P} "${libdir}"
        @- ${ECHO} "AR ->" ${libmruby_core_static} ${PP}
        ${PPQ} ${AR} #{build.archiver.archive_options % { outfile: "${libmruby_core_static}", objs: "${libmruby_core_objs}" }}
      ${libmruby_static}: ${libmruby_objs}
        @- ${MKDIR_P} "${libdir}"
        @- ${ECHO} "AR ->" ${libmruby_static} ${PP}
        ${PPQ} ${AR} #{build.archiver.archive_options % { outfile: "${libmruby_static}", objs: "${libmruby_objs}" }}

      #{
        # FIXME: gem.export_include_paths を個別の gem 単位に適用する

        #p build.bins.flatten.sort
        #p build.bins.flatten.sort - build.gems.map { |e| e.bins }.flatten; 0/0
        build.gems.map do |g|
          bins = (g.name == "mruby-bin-mrbc") ? ["mrbc"] : g.bins.flatten.sort
          libmruby_name = (g.name == "mruby-bin-mrbc") ? "mruby_core" : "mruby" # TODO?: 利用する libmruby.a をメソッドで取得する？
          bins.map do |bin|
            bin1 = File.join(build.build_dir, "bin", bin)
            t = Rake::Task.tasks.find { |e| e.name == bin1 }
            objs0 = t.prerequisites.sort
            lib1 = build.libfile("/lib/libmruby")
            lib2 = build.libfile("/lib/libmruby_core")
            objs0.delete_if { |e| e.end_with?(lib1) || e.end_with?(lib2) }
            objs = objs0.replace_prefix_by({ build.build_dir => "${WORKDIR}" })
            [
              # TODO: gem 固有の cflags やら ldflags やら libraries やらを適用する
              <<~BINTASK,
                ${WORKDIR}/bin/#{bin}: ${lib#{libmruby_name}_static} \\\n\t\t#{objs.join(" \\\n\t\t")}
                  @- ${MKDIR_P} "${bindir}"
                  @- ${ECHO} "LD -> ${WORKDIR}/bin/#{bin}" ${PP}
                  ${PPQ} ${LD} ${LDFLAGS} ${library_paths} -o "${WORKDIR}/bin/#{bin}" #{objs.join(" ")} -l#{libmruby_name} ${libraries}
              BINTASK
              *objs.map { |obj|
                obj0 = obj.sub("${WORKDIR}") { build.build_dir }
                srcs = Rake::Task[obj0].prerequisites.sort.uniq.replace_prefix_by({ g.dir => "${SRCDIR}/mrbgems/#{g.name}" }.merge(srcdir_map))
                srcs.delete_if { |e| e.end_with?("/mrbgem.rake") || e.end_with?(".rb") }
                <<~TASK
                  #{obj}: \\\n\t\t#{srcs.join(" \\\n\t\t")}
                    @- ${MKDIR_P} "#{File.dirname obj}"
                    @- ${ECHO} "CC -> #{obj}" ${PP}
                    ${PPQ} ${CC} ${CFLAGS} ${defines} ${include_paths} #{incdir} -c -o "#{obj}" #{srcs.join(" ")}
                TASK
              }
            ]
          end
        end.flatten.join
      }

      #{
        # FIXME: gem.export_include_paths を個別の gem 単位に適用する

        [*libmruby_core_objs, *libmruby_objs].flatten.uniq.sort.each_with_object("") { |obj, a|
          src = obj.sub(/\.o$/, ".c")
          a << <<~TASK
            #{obj.replace_prefix_by(workdir_map)}: #{src.replace_prefix_by(srcdir_map)}
              @- ${MKDIR_P} "#{File.dirname obj.replace_prefix_by(workdir_map)}"
              @- ${ECHO} "CC -> #{obj.replace_prefix_by(workdir_map)}" ${PP}
              ${PPQ} ${CC} ${CFLAGS} ${defines} ${include_paths} #{incdir} -c -o "#{obj.replace_prefix_by(workdir_map)}" #{src.replace_prefix_by(srcdir_map)}
          TASK
        }
      }

      about:
        #{
          <<~HELP.to_make_echo
            ABOUT:
              This Makefile is generated by projects using, and builds a customised mruby.
              See the following URL for more details on how to generation this file:
                https://github.com/mruby/mruby/blob/master/doc/guides/compile.md
                https://github.com/mruby/mruby/blob/master/doc/guides/makefile.md

            mruby version: #{MRuby::Source::MRUBY_VERSION}
            Makefile generated date: #{Time.now.strftime "%Y-%m-%d"}
            Makefile generated configuration file: #{File.basename MRUBY_CONFIG}
            Makefile generated target name: #{build.name}
            included mrbgems:#{gemsinfo}
            required tools:
              ar
              cc
              ld
              make
              sh
            required libraries:
              libm
          HELP
        }

      help:
        #{
          <<~HELP.to_make_echo
            HELP: build customised mruby

            make with tasks:
              $ make about        # about mruby and mrbgems
              $ make all          # build customised mruby (default task)
              $ make clean        # cleanup working object files
              $ make help         # print this message
              $ make install      # install mruby on the system

            make with variables:
              $ make V=1          # echo the command
              $ make SRCDIR=...   # specifies a top directory of source code
              $ make WORKDIR=...  # specifies a working directory
              $ make CC=cc
              $ make CXX=c++
              $ make AS=as
              $ make LD=cc
              $ make AR=ar
              $ make CFLAGS=...
              $ make LDFLAGS=...
          HELP
        }
    MAKEFILE
  end

  coresrc_map = { MRUBY_ROOT => prefix }
  MRuby.each_distribution_file do |path|
    dest = path.replace_prefix_by(coresrc_map)
    file_copy_task path, dest, headup: headup
  end

  if build.presym_enabled?
    %w(include/mruby/presym/id.h include/mruby/presym/table.h).each do |e|
      src = File.join(build.build_dir, e)
      dest = File.join(prefix, e)
      file src => File.join(build.build_dir, "presym")
      file_copy_task src, dest, headup: headup
    end
  end

  build.libmruby_objs.flatten.uniq.map { |obj|
    t = Rake.application.lookup(obj)&.prerequisite_tasks
  }.flatten.compact.uniq.each { |tt|
    # TODO: tt.name が build.build_dir や gem.build_dir の場合は tt.prerequisites を再帰的に辿る

    case
    when g = build.gems.sort_by { |g| g.dir.size }.reverse.find { |g| tt.name.start_with?(g.dir) }
      dest = tt.name.replace_prefix_by({ g.dir => File.join(prefix, "mrbgems", g.name) })
    when tt.name.start_with?(build.build_dir)
      dest = tt.name.replace_prefix_by({ build.build_dir => prefix })
    else
      dest = tt.name.replace_prefix_by({ MRUBY_ROOT => prefix })
    end

    file_copy_task tt.name, dest, headup: headup
  }

  if build.enable_gems?
    build.gems.each do |g|
      gemdir = Pathname.new(g.dir)
      g.each_distribution_file do |path|
        path = (gemdir + path).to_s
        file_copy_task path, path.replace_prefix_by({ g.dir => File.join(prefix, "mrbgems", g.name) }), headup: headup
      end
    end
  end
end

__END__

 (cd /usr/local/lib/ruby/gems/3.3/gems/rake-13.2.1 && gview -p lib/rake/task.rb lib/rake/application.rb lib/rake/task_manager.rb)
