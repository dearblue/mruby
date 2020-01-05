assert "refinements with eval" do
  module Sandbox1
    module Extensions
      refine Object do
        def refine1
          12345
        end
      end
    end

    assert_raise NoMethodError do
      eval "refine1()"
    end

    assert_nothing_raised do
      eval "using Extensions"
    end

    assert_raise NoMethodError do
      eval "refine1()"
    end

    assert_equal 12345 do
      eval <<~CODE
        using Extensions
        refine1
      CODE
    end

    assert_raise NoMethodError do
      eval "refine1()"
    end

    using Extensions

    assert_equal 12345 do
      eval <<~CODE
        refine1
      CODE
    end
  end
end
