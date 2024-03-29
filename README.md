# Colorful-MHX3gx

![](https://user-images.githubusercontent.com/46832957/142984867-329de07d-47a5-4a1d-8ca4-634eedf1ddd8.png) ![](https://img.shields.io/github/downloads/ponpoko094/Colorful-MHX3gx/total) ![](https://img.shields.io/github/languages/code-size/ponpoko094/Colorful-MHX3gx) ![visitor badge](https://visitor-badge.glitch.me/badge?page_id=ponpoko094.Colorful-MHX3gx)

## とりあえずチートしたい方へ

この3gxには、まだ未確認のバグがあるかもしれません。そういったのが気になる方は舞姫氏のActionReplayチートを使ってください。 [舞姫のあっぷろーだー](https://ux.getuploader.com/1456723/download/9)

## はじめに

このプラグインはもともと舞姫氏のActionReplayチートがベースとなっています。
ぽこはそれをフォークし、3gxならではの機能（キーボードやOSD等）を用いてさらに使いやすくしようとしました。しかし、最初の頃はバグだらけでコンパイル時にはいつもエラー文が出ていました。ですが、ぽこは多くの3gx開発者にアドバイスを頂き、ここまで成長できました。本当に感謝しています。

## プラグインの紹介

チートの種類は200種類近くあるので、きっと使いたいチートが見つかるはずです。ネタチートもありますが、ほとんどのチートはニーズに沿っていることを考えているので心配ありません。もしMHX3gxだけだと物足りない場合はActionReplayを使えるようにしてあるので、ユーザーが作ったコードで遊ぶこともできます。

また、おまけも充実しています。電卓やアドレスを監視するプログラムもあれば、CTRPFのUIの色を自分好みにカスタマイズするプログラム（開発段階）もあります。

## Colorful-MHX3gxを使うためには

1. [Luma3ds](https://github.com/Nanquitas/Luma3DS/releases/)
   からboot.firmをダウンロードし、SDカードの一番上の階層にコピーしてください。
2. [Colorful-MHX3gx/releases](https://github.com/ponpoko094/Colorful-MHX3gx/releases)
   からMHX3gx.3gxをダウンロードしてください。
3. Colorful-MHX3gx.3gxをSDカードの`luma\plugins\0004000000155400`
   の中にコピーしてください。もしもフォルダーがなかったら作成してください。
4. 3DSを起動し、ホームメニューで`L+↓+Select`を押しRosalina menuを開き、Plugin Loaderの項目を
   **Enabled** にしてください。
5. MHXを起動し、画面が一瞬青く光ったら使えます。

## Colorful-MHX3gxのベータ版を使うためには

1. [Github Actions](https://github.com/ponpoko094/Colorful-MHX3gx/actions/workflows/make.yml)
   の一番上にある✅アイコンの横のリンクに飛んでください。
2. `Artifacts`の`Colorful-MHX3gx.3gx`を押すと、自動的に3gxのダウンロードが開始されます。
3. zip形式で保存されるため、`7-zip`等の解凍ソフトを使い3gxを取り出してください。

## 開発者向け

### 何のプログラミング言語で開発しているの？

この3gx自体は主にC++で書かれています。また、pythonを使って3dsに3gxの送信をしています。

### フレームワークやライブラリは何を使ってるの？

[CTRPluginFramework](https://github.com/mariohackandglitch/CTRPluginFramework-BlankTemplate)
と [libctru](https://github.com/devkitPro/libctru) を使っています。

### MHX3gxをコンパイルするにはどうすればいいの？

#### 必要なファイル

#### [devkitpro](https://github.com/devkitPro/installer/releases/latest)

exeファイルを開きインストールしてください。

#### [3gxtool(v1.1)](https://gitlab.com/thepixellizeross/3gxtool/-/releases)

解凍し、`C:\devkitPro\tools\bin`にコピーしてください。

#### [libCTRPF(v0.7.4)](https://gitlab.com/thepixellizeross/ctrpluginframework/-/releases)

解凍し、中にあるincludeとlibフォルダーを`C:\devkitPro\libctrpf`
の中にコピーしてください。もしもフォルダーがなかったら作成してください。

<details><summary>gxman by @HIDE810 （※v0.7.1以下のソースをコンパイルする時に使用してください。）</summary>

gxmanは、3gxtoolのインストールを簡単に行うためのプロジェクトです。

Windows & Linux に対応しています。

Golang(1.16以上) がお使いのシステムにインストールされている場合、以下のコマンドでインストールができます。

`go install github.com/HIDE810/gxman@latest`

1 MiBの制限がない最新の3gxtoolをインストールしたい場合は、以下のコマンドを使用します。

`gxman get -u`

</details>

### コンパイル方法

フォルダの名前に括弧等の一部の記号が含まれているとコンパイルエラーを起こします。

| 結果 | フォルダ名 |
| :-: | :-------------------: |
| ✅ |   `Colorful-MHX3gx`   |
| ✅ |  `Colorful-MHX3gx_1`  |
| ❌ | `Colorful-MHX3gx (1)` |

`build.bat`を起動してください。または、**Colorful-MHX3gxフォルダー上**で`make re`コマンドを動かしてください。

### どうやって3dsに3gxを送信すればいいの？

3ds側で[FTPD](https://github.com/mtheall/ftpd/releases/latest)
を使ってFTPサーバーを立てた状態で、

`make ftp`コマンドを動かすと、ファイルの送信が行われます。

`make send`コマンドを動かすと、コンパイルとファイルの送信が同時に行われます。

### どうやってCitraに3gxを送信すればいいの？

CTRPFがv0.7.4になったことで、3DSエミュレータである[Citra Nightly](https://citra-emu.org/download/)
上で3gxが動かせられるようになりました。

`make citra`コマンドを動かすと、`%APPDATA%\Citra\sdmc\luma\plugins\0004000000155400`
にファイルの送信が行われます。

また、`sendcitra.bat`を起動することでもファイルの送信ができます。

## クレジット（協力して頂いた人たち、また参考にしたサイト）

### ソースの記述

* ぽんぽこ
* HIDE810

### サーチした人

* ぽんぽこ
* 舞姫
* ymyn
* Fort42

### プラグイン作成において、アドバイス（ヒント）を頂いた人

* Naoki
* クレラビ
* だいち村長
* けんじい
* Kominost

### 参考にしたサイト

[kiranico](http://mhgen.kiranico.com)

[AtCoder](https://atcoder.jp/contests/APG4b)

## さいごに

もしぽこの開発環境に興味があったら → [ぽこの開発環境紹介](https://gist.github.com/ponpoko094/586fd8a17122d8fd1f028211f2465144)

バグ報告等はTwitter [@ponpoko094](https://twitter.com/ponpoko094) までどうぞ！

## License

Colorful-MHX3gx is licensed under the [MIT License](LICENSE)

Colorful-MHX3gx 2019-2023
