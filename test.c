#if 0
$stdout.sync = true

puts "===== Call bin\\mruby-config ====="
system "bin\\mruby-config --cc --cflags --ld --ldflags --libs" or raise "failed"

puts
puts "===== Call build\\host\\bin\\mruby-config ====="
system "build\\host\\bin\\mruby-config --cc --cflags --ld --ldflags --libs" or raise "failed"

puts
puts "===== Oneshot compile to object file ====="
cmd = %(#{%x(bin\\mruby-config.bat --cc --cflags)} /c test.c).tr("\n", " ")
puts cmd
system cmd or raise "failed"

puts
puts "===== Oneshot link ====="
cmd = %(#{%x(bin\\mruby-config.bat --ld --ldflags --libs)} test.obj).tr("\n", " ")
puts cmd
system cmd or raise "failed"

puts
puts "===== Launch test.exe ====="
system %(.\\test.exe) or raise "failed"

__END__
#endif

#include <mruby.h>
#include <mruby/compile.h>

int
main(int argc, char *argv[])
{
  mrb_state *mrb = mrb_open();
  mrb_load_string(mrb, "puts %(I am #{MRUBY_DESCRIPTION})");
  mrb_close(mrb);

  return 0;
}
