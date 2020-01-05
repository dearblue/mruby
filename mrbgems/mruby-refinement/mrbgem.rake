MRuby::Gem::Specification.new('mruby-refinement') do |spec|
  spec.license = 'MIT'
  spec.author  = 'mruby developers'
  spec.summary = "the Ruby's refinements feature"

  spec.build.defines << 'MRB_USE_REFINEMENT'

  spec.add_test_dependency 'mruby-eval', core: 'mruby-eval'
  spec.add_test_dependency 'mruby-method', core: 'mruby-method'
  spec.add_test_dependency 'mruby-metaprog', core: 'mruby-metaprog'
end
