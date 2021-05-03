MRuby::Gem::Specification.new('mruby-io') do |spec|
  spec.license = 'MIT'
  spec.authors = ['Internet Initiative Japan Inc.', 'mruby developers']
  spec.summary = 'IO and File class'

  spec.cc.include_paths << "#{build.root}/src"

  if spec.for_windows?
    spec.linker.libraries << "ws2_32"
  end
  spec.add_test_dependency 'mruby-time', core: 'mruby-time'

  spec.terms << {
    "README.md" => proc {
      pattern = /Copyright \(c\) 2013 Internet Initiative Japan Inc\..*?DEALINGS IN THE SOFTWARE\.\n/m
      File.extract(File.join(spec.dir, "README.md"), pattern).gsub(/^\s*\*+ */, "")
    }
  }
end
