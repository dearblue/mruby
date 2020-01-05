assert "リファインメントは using してから有効になる" do
  module Sandbox
    assert_nothing_raised do
      module Extensions
        refine Object do
          def refine_12345
            12345
          end
        end
      end
    end

    assert_raise NoMethodError do
      # CRuby で確認する場合のために明示的なメソッド呼び出しを行う
      refine_12345()
    end

    assert_nothing_raised do
      using Extensions
    end

    assert_nothing_raised { refine_12345 }
    assert_equal 12345, refine_12345
    assert_equal 12345, -> { refine_12345 }[]
    assert_equal 12345, (class Object; refine_12345; end)
  end
end

assert "メソッドの中では using 出来ない" do
  class Module
    def sandbox_a
      using Sandbox::Extensions
    end
  end

  assert_raise_with_message RuntimeError, "Module#using is not permitted in methods" do
    Kernel.sandbox_a
  end

  def sandbox_b
    using Sandbox::Extensions
  end

  assert_raise_with_message RuntimeError, "main.using is permitted only at toplevel" do
    sandbox_b
  end
end

assert "リファインメントはモジュール・クラスのスコープが異なると無効になる" do
  module Sandbox
    assert_raise NoMethodError do
      refine_12345()
    end
  end
end

assert "リファインメントを有効にすると内部のスコープでも有効になる" do
  module Sandbox
    using Sandbox::Extensions

    module InnerSandbox
      assert_equal 12345, refine_12345
    end
  end
end

assert "using は別のモジュールで定義されたリファインメントを有効にしない" do
  module AnotherSandbox
    assert_nothing_raised do
      module Extensions
        refine Kernel do
          def refine_abcdef
            "abcdef"
          end
        end
      end
    end

    assert_raise NoMethodError do
      refine_abcdef()
    end

    assert_nothing_raised do
      using Extensions
    end

    assert_raise NoMethodError do
      refine_12345()
    end

    assert_equal "abcdef", refine_abcdef
  end

  class Object
    remove_const :AnotherSandbox
  end
end

assert "Module#refine にはクラス・モジュールしか渡せない" do
  module Sandbox
    module Extensions
      assert_raise TypeError do
        refine Object.new do
        end
      end

      assert_raise TypeError do
        refine "ABCDEF" do
        end
      end
    end
  end
end

assert "リファインメントはラムダの中で有効化されたらスコープを辿って有効になる" do
  module Sandbox
    module InnerSandbox
      assert_nothing_raised do
        -> { using Sandbox::Extensions }.call
      end

      assert_equal 12345 do
        refine_12345
      end
    end

    assert_raise NoMethodError do
      refine_12345()
    end
  end
end

assert "同じモジュールスコープで定義されたメソッドはrefinementが有効である" do
  module Sandbox
    module Extensions
      refine String do
        def scope1
          refine_12345
        end

        def scope2
          scope1
        end
      end
    end

    using Extensions

    assert_equal 12345 do
      "".scope2
    end
  end
end

assert "リファインメントメソッドからsuperするともとのクラスのメソッドが呼ばれる" do
  module Sandbox
    module Extensions
      refine String do
        def slice(off, size)
          super.upcase
        end
      end
    end

    using Extensions

    assert_equal "CDE" do
      "abcdefg".slice(2, 3)
    end
  end
end

assert "using の前と後ろで定義されたメソッド内では見え方が違う" do
  module AnotherSandbox
    module Extensions
      refine String do
        def to_s
          upcase
        end
      end
    end

    def self.astr1(str)
      str.to_s
    end

    using Extensions

    def self.astr2(str)
      str.to_s
    end

    assert_equal "abcdefg" do
      astr1 "abcdefg"
    end

    assert_equal "ABCDEFG" do
      astr2 "abcdefg"
    end
  end

  class Object
    remove_const :AnotherSandbox
  end
end

assert "using は include されたモジュールも有効になる" do
  module AnotherSandbox
    module Extensions
      include Sandbox::Extensions
    end

    using Extensions

    assert_equal 12345 do
      refine_12345
    end
  end

  class Object
    remove_const :AnotherSandbox
  end
end

assert "using は prepend されたモジュールも有効になる" do
  module AnotherSandbox
    module Extensions
      prepend Sandbox::Extensions
    end

    using Extensions

    assert_equal 12345 do
      refine_12345
    end
  end

  class Object
    remove_const :AnotherSandbox
  end
end
