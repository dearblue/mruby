MRuby::Gem::Specification.new('mruby-string-ext') do |spec|
  spec.license = 'MIT'
  spec.author  = 'mruby developers'
  spec.summary = 'String class extension'
  spec.add_test_dependency 'mruby-enumerator', core: 'mruby-enumerator'
  spec.add_dependency 'mruby-error', core: 'mruby-error'
end
