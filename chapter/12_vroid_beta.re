= 新しいVRoidの未来をベータ版で覗いてみる

〆切も差し迫ったある日、VRoid Studioにアバターの着せ替え機能を実装するという発表@<bib>{vroid-beta}がなされました。
これは既にある3Dキャラクターのモデルをxavater形式と呼ばれる独自形式にしてVRoid上でxwear形式に変換した衣装データを着せられるようにする機能です。
実際にベータに応募してみたのですが、使ってみると現時点ではこれからであると言わざるを得ません。

まず、VRoid衣装は既存の衣装には一切着せることができません。
着せられるのはxwear形式に変換した衣装データのみです。
で、各ボーンを移動・回転・拡大・縮小させて着せていくことになります。正直、できることは現状キセテネとあまり変わらないのです。
なお、自動フィット機能である程度までは着せることができますが、そこから先は手動で行った方が確実です。
なお、VRoidアバターの着せ替えのために作ったVRoid衣装をxwear形式に変換したのですが、ラスクちゃんではうまく読み込めませんでした。
さらに、靴を読み込むことはできましたが、衣装内のアーマチュアにHipsのボーンがないと履かせられないのです。
しかし、UltimateKissmaちゃんの服をラスクちゃんに着せる@<fn>{rusk}ところはなんとかうまくいきました。

//image[rusk-kissma-vysyvanka][UltimateKissmaちゃんの服をラスクちゃんに着せる][scale=0.6]{
//}

//footnote[rusk][しかし、こまどアバターの胸に合わせることまではできませんでした……]

これが、VRoid衣装に対応してくれたらと思うのですが、VRoid衣装が通常の衣装より安い以上、クリエイターの制作意欲を奪わないようにという配慮がされているのだと思います。

また、Android対応のような軽量化は考慮されていません。
なので、出力されたアバターは実質PC専用と考えた方がよいでしょう。
さらに、ギミックなどに関しては別途仕込む必要があります。
なので、Blenderを使わなくてもUnityで何とかしなければいけないという現状は何ら変わってはいません。
VRM形式にもエクスポートはできますが、なんとバージョン1.0にしか対応していません。
Clusterを初めとして、VRM形式は多くのソフトウェアやプラットフォームが採用していますが、バージョン1.0への対応は進んでいないのが現実です。
なので、VRChatのアバターをClusterで使うということもできない状態です。
まだベータ版ということもあり、現時点では、まだまだ使うのは難しいと思います。

しかしながら、VRM形式に出力できるということはClusterにアバターをアップロードしやすくなるということでもあります。
そして、それらの機能は要望ベースでいずれ実装されることでしょう。
となると、いつもの姿でVRChat以外の場にも行けるということになります。
なので、私は楽しみにVRoidの成長を見守りたいと思います。