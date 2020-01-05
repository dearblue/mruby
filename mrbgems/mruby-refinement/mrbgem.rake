MRuby::Gem::Specification.new('mruby-refinement') do |spec|
  spec.license = 'MIT'
  spec.author  = 'mruby developers'
  spec.summary = 'the refinements feature'

  spec.add_dependency 'mruby-class-ext', core: 'mruby-class-ext'
  spec.add_test_dependency 'mruby-eval', core: 'mruby-eval'
  spec.add_test_dependency 'mruby-binding', core: 'mruby-binding'
end
