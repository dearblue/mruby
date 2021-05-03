MRuby::Gem::Specification.new('mruby-sleep') do |spec|
  spec.license = 'MIT'
  spec.authors = ['MATSUMOTO Ryosuke', 'mruby developers']
  spec.summary = 'Kernel#sleep and Kernel#usleep'

  spec.terms << {
    "src/sleep.c" => proc {
      pattern = /Copyright \(c\) mod_mruby developers 2012-.*?SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE\.\n/m
      File.extract(File.join(spec.dir, "src/sleep.c"), pattern).gsub(/^\s*\*+ */, "")
    }
  }
end
