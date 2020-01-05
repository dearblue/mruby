assert "refinement1" do
  assert_nothing_raised do
    module Refine1
      refine Object do
        def refine1
          12345
        end
      end
    end
  end

  module RefineSandbox
    assert_raise NoMethodError do
      refine1
    end

    assert_nothing_raised do
      using Refine1
    end

    assert_equal 12345, refine1
    assert_equal 12345, -> { refine1 }[]
    assert_equal 12345, (class Object; refine1; end)
  end
end

assert "refinement2" do
  assert_nothing_raised do
    module Refine2
      refine Kernel do
        def refine2
          "abcdef"
        end
      end
    end
  end

  module RefineSandbox
    assert_raise NoMethodError do
      refine1
    end

    assert_raise NoMethodError do
      refine2
    end

    assert_nothing_raised do
      using Refine2
    end

    assert_equal "abcdef", refine2
  end
end

assert "refinement3" do
  # raised '"ABCDEF" is not class/module'
  assert_raise TypeError do
    module Refine3
      refine "ABCDEF" do
      end
    end
  end
end

assert "refinement4" do
  assert_nothing_raised do
    -> { using Refine1 }[]
  end

  assert_equal 12345, refine1
end

assert "同じモジュールスコープで定義されたメソッドはrefinementが有効である" do
  module RefineSandbox
    module RefineTestScope
      refine String do
        def scope1
          "scope1"
        end

        def scope2
          scope1
        end
      end
    end

    using RefineTestScope
    assert_equal "scope1", "".scope2
  end
end

assert "リファインメントメソッドからsuperするともとのクラスのメソッドが呼ばれる" do
  module RefineSandbox
    module Refine4
      refine String do
        def slice(off, size)
          super.upcase
        end
      end
    end

    using Refine4

    assert_equal "CDE", "abcdefg".slice(2, 3)
  end
end
