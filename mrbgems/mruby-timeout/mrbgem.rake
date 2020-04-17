MRuby::Gem::Specification.new('mruby-timeout') do |spec|
  spec.license = 'MIT'
  spec.author  = 'mruby developers'
  spec.summary = 'Timeout module'

  if build.exts.executable == '.exe'
    linker.libraries << "winmm"
  end

  add_test_dependency 'mruby-sleep', core: 'mruby-sleep'
  add_test_dependency 'mruby-rational', core: 'mruby-rational'
end
