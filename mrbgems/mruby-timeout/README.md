# mruby-timeout

`Timeout` module for mruby.

## Limitations

- The resolution is 1 millisecond.
- The lower accuracy of the timer used inside the implementation is preferred.
  The purpose of this is to reduce the polling load for interrupt handling.
- As with CRuby, it doesn't work, for example, while processing a C function.
  If the call to `mrb_interrupt_check()` is made periodically, it can be interrupted.

## Implemented APIs

- module `Timeout`
- class `Timeout::Error`
- method `Timeout.timeout`
