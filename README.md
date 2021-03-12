# MHX3gx

## はじめに
このプラグインはもともと舞姫氏のActionReplayチートがベースとなっています。
ぽこはそれをフォークし、3gxならではの機能（キーボードやOSD等）を用いてさらに使いやすくしようとしました。しかし、最初の頃はバグだらけでコンパイル時にはいつもエラー文が出ていました。ですが、ぽこは多くの3gx開発者にアドバイスを頂き、ここまで成長できました。本当に感謝しています。

このプラグインは主にC++で書かれていて、[CTRPluginFramework(v0.7.0)](https://github.com/mariohackandglitch/CTRPluginFramework-BlankTemplate){:target="_blank"}をベースとしています。

## プラグインの紹介
チートの種類は200種類近くあるので、きっと使いたいチートが見つかるはずです。ネタチートもありますが、ほとんどのチートはニーズに沿っていることを考えているので心配ありません。もしMHX3gxだけでは物足りない場合はActionReplayを使えるようにしてあるので、ユーザーが作ったコードで遊ぶこともできます。

また、おまけも充実しています。電卓やアドレスを監視するプログラムもあれば、CTRPFのUIの色を自分好みにカスタマイズするプログラム（開発段階）もあります。
## MHX3gxを使うためには
1. [Luma3ds v10.2.1](https://github.com/Nanquitas/Luma3DS/releases/tag/v10.2.1){:target="_blank"}からboot.firmをダウンロードし、SDカードの一番上の階層にコピーしてください。
2. [MHX3gx/releases](https://github.com/ponpoko094/MHX3gx/releases){:target="_blank"}からMHX3gx.3gxをダウンロードしてください。
3. MHX3gx.3gxをSDカードの`luma\plugins\0004000000155400`の中にコピーしてください。もしもフォルダがなかったら作成してください。
4. 3DSを起動し、ホームメニューで`L+↓+Select`でRosalina menuを開き、Plugin Loaderの項目を**Enabled**にしてください。
5. MHXを起動し、画面が一瞬青く光ったら使えます。
## MHX3gxをコンパイルするには

### 必要なファイル
### [devkitpro](https://github.com/devkitPro/installer/releases){:target="_blank"}
exeファイルを開きインストールしてください。
### [3gxtool](https://cdn.discordapp.com/attachments/479233979271086090/707634663765573753/3gxtool.exe){:target="_blank"}
`C:\devkitPro\tools\bin`にコピーしてください。

**※CTRPFv0.5.1のコンパイル時に必要となる3gxtool.exeはMHX3gxでは使えません。**
### [libCTRPF](https://cdn.discordapp.com/attachments/479233979271086090/803683007067848774/libctrpf-0.7.0-0ad93110.zip){:target="_blank"}
解凍し、中にあるincludeとlibフォルダを`C:\devkitPro\libctrpf`の中にコピーしてください。もしもフォルダがなかったら作成してください。

### コンパイル方法
build.batを起動してください。または、**MHX3gxフォルダ上**で`make re`コマンドを動かしてください。

## クレジット（協力して頂いた人たち、また参考にしたサイト）
ソースの記述 ぽんぽこ

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

### 参考にしたサイト
[kiranico](http://mhgen.kiranico.com/){:target="_blank"}

[AtCoder](https://atcoder.jp/contests/APG4b){:target="_blank"}

## さいごに
プルリクエストは大歓迎です！

バグ報告等は Twitter [@ponpoko094](https://twitter.com/ponpoko094){:target="_blank"} までどうぞ！

MHX3gx 2019-2021