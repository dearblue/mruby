module Timeout
  # @overload timeout(sec, exception_class = nil) { |sec| ... } -> object
  # @overload timeout(sec, exception_class, message) { |sec| ... } -> object
  #
  # @param sec
  # @param [Exception] exception_class
  # @param [String] message
  # @return yield returned value
  #
  # 制限:
  # sec に対して与えられた1秒未満の値 (Float や Rational) の分解能は1ミリ秒です (端数は切り捨てられます)。
  # MRB_INT32の場合、指定できるのは最大約24日です (かつMRB_WORD_BOXINGの場合は最大約12日)。
  def Timeout.timeout(sec, exc = nil, mesg = nil)
    tag = nil
    res = lambda {
      tag = _regist_timeout(1000 * sec)
      yield(sec)
    }.call

    return res unless tag === res

    exc ||= Timeout::Error
    mesg ||= "execution expired"
    bt = (class << tag; @backtrace; end)
    e = exc.new(mesg)
    e.set_backtrace(bt)
    raise e
  ensure
    _unregist_timeout(tag)
  end

  class Error < RuntimeError
  end
end

TimeoutError = Timeout::Error

module Kernel
  def timeout(*args, &b)
    Timeout.timeout(*args, &b)
  end
end
