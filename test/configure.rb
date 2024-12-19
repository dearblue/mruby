require "fileutils"
require "tmpdir"
require_relative "assert"

MRUBY_ROOT ||= File.dirname __dir__

tmpdir = Dir.mktmpdir("mruby-config-test")
at_exit { FileUtils.rm_rf tmpdir }

def tmpdir.write(fname, body, *args)
  path = File.join(self, fname)
  File.write(path, body, *args)
  path
end

serialno = 0
define_method :assert_config, &->(expect, code) {
  env = {
    "MRUBY_CONFIG" => tmpdir.write("build_config#{serialno += 1}.rb", code + <<~'CODE')

      task "report-build-targets" do |t|
        puts MRuby.targets.values.map(&:name).sort.join " "
      end
    CODE
  }
  cmd = %W(rake -f#{File.join(MRUBY_ROOT, "Rakefile")} report-build-targets)
  result = IO.popen(env, cmd, mode: "r", err: File::NULL, &:read).chomp

  cond = expect === result
  unless cond
    diff = "   expected #{result.inspect} to be match #{expect.inspect}"
  end

  assert_true cond, nil, diff
}

puts ">>> build configuration test <<<"

assert "build configuration" do
  assert_config "host1 host1/mrbc host2", <<~'BUILD_CONFIG'
    MRuby::Build.new("host1") do
      toolchain "gcc"
    end

    MRuby::Build.new("host2") do
      toolchain "gcc"
    end
  BUILD_CONFIG

  assert_config "host1 host1/mrbc host2", <<~'BUILD_CONFIG'
    MRuby::Build.new("host1") do
      toolchain "gcc"
    end

    MRuby::Build.new("host2") do
      toolchain "gcc"
      disable_presym
    end
  BUILD_CONFIG

  assert_config "host1 host2", <<~'BUILD_CONFIG'
    MRuby::Build.new("host1") do
      toolchain "gcc"
    end

    MRuby::Build.new("host2") do
      toolchain "gcc"
      disable_presym
      gem core: "mruby-bin-mrbc"
    end
  BUILD_CONFIG

  assert_config "host1 host1/mrbc host2", <<~'BUILD_CONFIG'
    MRuby::Build.new("host1") do
      toolchain "gcc"
    end

    MRuby::Build.new("host2") do
      toolchain "gcc"
      gem core: "mruby-bin-mrbc"
    end
  BUILD_CONFIG
end

assert "cross build configuration" do
  assert_config "cross1 cross2 host", <<~'BUILD_CONFIG'
    MRuby::CrossBuild.new("cross1") do
      toolchain "gcc"
    end

    MRuby::CrossBuild.new("cross2") do
      toolchain "gcc"
      disable_presym
      gem core: "mruby-bin-mrbc"
    end
  BUILD_CONFIG
end

exit report
