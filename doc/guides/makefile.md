# Generating `Makefile`

`rake makefile` (より詳しくいうと `rake makefile:suite:#{build.name}`) によってカスタマイズ済みの libmruby をビルドするためのファイル一式を出力することが出来ます。
出力ディレクトリは `#{build.build_dir}/makefile/mruby-x.y.z/` です。
出力されたディレクトリを `tar` や `zip` でまとめたり、取り込んだりすることが可能であり、対象ディレクトリに移動して `make` コマンドを発行することで libmruby がビルドされます。

出力される libmruby は `rake makefile` を行った時点で機能が固定されるため、大本の mruby とは異なり mrbgems を変更する方法がありません。
その代わりビルドするためのツールは、ベースシステムにあるものだけで満足できることが期待されます。
必要な最低限のツールを具体的に述べると、`cc` (C コンパイラ)、`ar` (アーカイバ)、`ld` (リンカ)、`make`、`sh` くらいです。

ただし `rake makefile` した時の mrbgems が、その他のツールを必要とする可能性があることに注意して下さい。

