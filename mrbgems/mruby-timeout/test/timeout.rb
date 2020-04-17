assert "timeout" do
  expire = 10 / 1000r
  usleeping = 20000

  assert_equal(5) { Timeout.timeout(1) { 5 } }
  assert_raise(Timeout::Error) { Timeout.timeout(expire) { usleep usleeping } }
  assert_raise(RangeError) { Timeout.timeout(expire, RangeError) { usleep usleeping } }
  assert_raise(TypeError) { Timeout.timeout(expire) { raise TypeError } }

  assert_raise(IndexError) {
    Timeout.timeout(expire * 2, IndexError) {
      begin
        Timeout.timeout(expire) {
          usleep usleeping
        }
      ensure
        usleep usleeping
      end
    }
  }
end
