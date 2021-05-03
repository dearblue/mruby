MRuby::Gem::Specification.new('mruby-pack') do |spec|
  spec.license = 'MIT'
  spec.authors = ['Internet Initiative Japan Inc.', 'mruby developers']
  spec.summary = 'Array#pack and String#unpack method'

  spec.cc.include_paths << "#{build.root}/src"

  spec.terms << {
    "README.md" => proc {
      pattern = /Copyright \(c\) 2012 Internet Initiative Japan Inc\..*?DEALINGS IN THE SOFTWARE\.\n/m
      File.extract(File.join(spec.dir, "README.md"), pattern).gsub(/^\s*\*+ */, "")
    }
  }
end
