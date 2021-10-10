# MHX3gx

![TotalDownloads](https://img.shields.io/github/downloads/ponpoko094/MHX3gx/total)
![Stars](https://img.shields.io/github/stars/ponpoko094/MHX3gx)
![CodeSize](https://img.shields.io/github/languages/code-size/ponpoko094/MHX3gx)

## とりあえずチートしたい方へ
この3gxには、まだ未確認のバグがあるかもしれません。そういったのが気になる方は舞姫氏のActionReplayチートを使ってください。
[舞姫のあっぷろーだー](https://ux.getuploader.com/1456723/download/9)

## はじめに
このプラグインはもともと舞姫氏のActionReplayチートがベースとなっています。
ぽこはそれをフォークし、3gxならではの機能（キーボードやOSD等）を用いてさらに使いやすくしようとしました。しかし、最初の頃はバグだらけでコンパイル時にはいつもエラー文が出ていました。ですが、ぽこは多くの3gx開発者にアドバイスを頂き、ここまで成長できました。本当に感謝しています。

## プラグインの紹介
チートの種類は200種類近くあるので、きっと使いたいチートが見つかるはずです。ネタチートもありますが、ほとんどのチートはニーズに沿っていることを考えているので心配ありません。もしMHX3gxだけだと物足りない場合はActionReplayを使えるようにしてあるので、ユーザーが作ったコードで遊ぶこともできます。

また、おまけも充実しています。電卓やアドレスを監視するプログラムもあれば、CTRPFのUIの色を自分好みにカスタマイズするプログラム（開発段階）もあります。
## MHX3gxを使うためには
1. [Luma3ds v10.2.1](https://github.com/Nanquitas/Luma3DS/releases/tag/v10.2.1)からboot.firmをダウンロードし、SDカードの一番上の階層にコピーしてください。
2. [MHX3gx/releases](https://github.com/ponpoko094/MHX3gx/releases)からMHX3gx.3gxをダウンロードしてください。
3. MHX3gx.3gxをSDカードの`luma\plugins\0004000000155400`の中にコピーしてください。もしもフォルダーがなかったら作成してください。
4. 3DSを起動し、ホームメニューで`L+↓+Select`を押しRosalina menuを開き、Plugin Loaderの項目を**Enabled**にしてください。
5. MHXを起動し、画面が一瞬青く光ったら使えます。

## 開発者向け

### 何のプログラミング言語で開発しているの？
この3gx自体は主にC++で書かれています。また、pythonを使って3dsに3gxの送信をしています。

### フレームワークやライブラリは何を使ってるの？
[CTRPluginFramework](https://github.com/mariohackandglitch/CTRPluginFramework-BlankTemplate)とC++標準ライブラリを使っています。

### MHX3gxをコンパイルするにはどうすればいいの？

#### 必要なファイル
#### [devkitpro](https://github.com/devkitPro/installer/releases/latest)
exeファイルを開きインストールしてください。
#### [3gxtool](https://cdn.discordapp.com/attachments/895927933724688387/896335750898020352/patched3gxtool.7z)
解凍し、`C:\devkitPro\tools\bin`にコピーしてください。
**※通常の3gxtool.exeはファイルサイズ制限が掛かっているのでMHX3gxでは使えません。**
#### [libCTRPF(v0.7.1)](https://cdn.discordapp.com/attachments/895927933724688387/896385805214449684/libctrpf-0.7.1-4bd18725.7z)
解凍し、中にあるincludeとlibフォルダーを`C:\devkitPro\libctrpf`の中にコピーしてください。もしもフォルダーがなかったら作成してください。

### コンパイル方法
build.batを起動してください。または、**MHX3gxフォルダー上**で`make re`コマンドを動かしてください。

### どうやって3dsに3gxを送信すればいいの？
3ds側で[FTPD](https://github.com/mtheall/ftpd/releases/latest)や[3DShell](https://github.com/joel16/3DShell/releases/latest)を使ってFTPサーバーを立てた状態で、

`make ftp`コマンドを動かすと、ファイルの送信が行われます。

`make send`コマンドを動かすと、コンパイルとファイルの送信が同時に行われます。

## クレジット（協力して頂いた人たち、また参考にしたサイト）
### ソースの記述
- ぽんぽこ

### サーチした人
- ぽんぽこ
- 舞姫
- ymyn
- Fort42

### プラグイン作成において、アドバイス（ヒント）を頂いた人
- Naoki
- クレラビ
- だいち村長
- けんじい
- Kominost

### 参考にしたサイト
[kiranico](http://mhgen.kiranico.com/)

[AtCoder](https://atcoder.jp/contests/APG4b)

## さいごに

もしぽこの開発環境に興味があったら → [ぽこの開発環境紹介](https://gist.github.com/ponpoko094/586fd8a17122d8fd1f028211f2465144)

バグ報告等はTwitter [@ponpoko094](https://twitter.com/ponpoko094) までどうぞ！

MHX3gx 2019-2021
