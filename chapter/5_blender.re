= アバターをBlenderで軽量化する

== Blenderと和解せよ！

残念ながら、UnityとVRoid Studioだけではたとえ水着だとしてもQuestでまともに表示させるアバターを作るのは難しいでしょう。
ボーン数を削ることに関してはかなり難しいですが、テクスチャを重ねてポリゴンを削る所まではBlenderでなんとかできます。
なので、早速VRM出力していきましょう。
設定に関しては、デフォルトのままで大丈夫です。マテリアル数も、ボーン数も減らさなくてよいでしょう。
なぜなら、マテリアルはBlenderで結合できるからです。
ひとまず髪を短くしたアバター@<fn>{short-hair}を用意し、出力してみるとボーン数は89、これならポリゴン数を削ればFallbackにできるかもしれません。

//image[short-hair][髪を短くしてVRM出力][scale=0.6]{
    【使用衣裳】白ワンピ：星井まゆき星空通販様、スク水：ここなふぁくとりー様、桜の髪飾り：リザのアトリエ様
//}

//footnote[short-hair][【使用衣裳】白ワンピ：星井まゆき星空通販様、スク水：ここなふぁくとりー様、桜の髪飾り：リザのアトリエ様]

さて、ここからはBlenderを使うのですが、必ずバージョン2系のBlenderを使用してください。
かつ、以下のプラグインが必要になります。

 * VRM Add-on for Blender@<fn>{vrm-blender}
 * Cats Blender Plugin@<fn>{cats-blender}
 * material-combiner-addon@<fn>{material-combiner-addon}

//footnote[vrm-blender][https://vrm-addon-for-blender.info/ja/]
//footnote[cats-blender][https://github.com/absolute-quantum/cats-blender-plugin]
//footnote[material-combiner-addon][https://github.com/Grim-es/material-combiner-addon]

これらを使用するとVRMをBlenderで扱うことができるようになります。

なぜバージョン2系のBlenderを使うかというと、プラグインがバージョン3系以降のBlenderに対応していないためです。
無理矢理対応させるにはプログラミングの知識が必要なので、プログラミングに自信のない方はやめておいた方が無難です。

なお、BlenderはPythonというプログラミング言語の実行環境が必要です。
OSに別のPythonがインストールされている場合、material-combiner-addonで必要なPillowという画像処理ライブラリのインストールに失敗する場合があります。
その場合は、Windowsの場合は以下のコマンドを実行する必要があります。

//cmd{
> set PythonPath="Your\Copied\Path\To\Python\bin\Folder"
> %PythonPath%\python.exe -m pip install Pillow --user --upgrade
//}

なお、「Your\Copied\Path\To\Python\bin\Folder」の部分は各自のフォルダに読み替えてください。

また、世の中にはMacでアバター改変を行っている方もいると思いますが、Macの場合は少々面倒です。
まず、Blenderを開きましょう。
その後で、ShiftキーとF4キーを同時に押すとPythonコンソールが開きます。
その後、以下のコードを貼り付ければPillowがインストールされます。

//source[blender-pillow-install.py]{
__import__('ensurepip')._bootstrap()
__import__('pip._internal')\
    ._internal.main(['install', '-U', 'pip', 'setuptools', 'wheel'])
__import__('pip._internal')._internal.main(['install', 'Pillow'])

//}

このようにして、Pillowをインストールし終えたらUnityでの改変準備は完了です。

== Blenderを開いたら

まず、Blenderを開くと最初に四角形が表示されていますが、これらは消します。
その後、使用するVRMをインポートすると画面にVRMアバターが表示されます。

//image[in-blender][blenderへインポートしたところ][scale=0.6]{
//}

== アバターのボーンの最適化

まずすべきは、アバターのボーンの最適化です。
VRoidアバターにはUpperChestというボーンがありますが、これがかつてVRChatでは悪さをしていたのです。
また、ここで最適化を施すことによって全身の状態をアバターに反映させるフルトラッキングを使った際におかしな動きをしないで済みます。

そのためには、CATSプラグインで設定をする必要があります。
Fix Modelsというボタンの隣にある、レンチのマークの付いた設定ボタンを押してください。
押すと設定が出てくるのでKeep End Bonesにチェックマークを付けてください。
これを設定すると末端のボーンが残るので、指が動かなくなるなどボーンが消えてしまったことによるバグに遭遇しなくてよくなります。

//image[keep-end-bones][Keep End Bonesの設定をオンにする][scale=0.6]{
//}

この後Fix Modelsボタンを押すとボーンが最適化され、ボーンの名前もVRoid独自の形式からVRChatでよくある名前に変わります。
これで、ボーンの最適化ができました。

== メッシュの分割

次に、CATSプラグインのModel Optionsを開き、マテリアル単位にメッシュを分割することです。
なお、1回では服のポリゴンがうまく分かれてくれないために悲惨なことになります。
顔のメッシュを分割するとシェイプキーが壊れるという話もありますが、ここは全部のメッシュを分割します。
だいたい15個前後のマテリアルになると思います。
なお、Questでは透過が使えないためここからテクスチャを編集して透過部分を削るという荒技をする人もいます。
しかし、Blenderと和解するにはかなりの時間がかかるかと思いますので今回は飛ばして先に進みます。

== ポリゴンの削減

メッシュの分割が終わったら、Decimationのタブを開きます。
まずはCustomを選択し、全てのシェイプキーを保護します。
なお、保護しないとシェイプキーが消えて表情が付けられなくなってしまうので必ず保護しましょう。
その後にSmartを選択し、Save Fingersを選んでTrisは10,000にしてQuick Decimationをクリックします。
失敗するとロボットのように指が分離してしまうので、Save Fingersは必ず選びましょう。
そしてポリゴン数を減らすと以下のような見た目になると思います。

//image[decimated][ポリゴン数を減らしたところ][scale=0.6]{
//}

== メッシュの結合

これが終わったらまずはメッシュを結合しましょう。
先ほどと同じCATSプラグインのModel Optionsを開くと結合できます。
これは一つにまとめてしまって大丈夫ですが、服を脱がすギミックを仕込みたい場合はメッシュは分けたままにしておくことも一つの解といえるでしょう。
なお、着せかえについては後述いたします。

== テクスチャの結合

これが終わったら、テクスチャを結合します。
まずは、Blenderのファイルを保存し、FileメニューからExternal Data内のUnpack All Into Filesを選びます。
その後に表示されるメニューではUse files in current directoryを選び、フォルダ内に保存しましょう。

//image[material][マテリアルを結合する][scale=0.6]{
//}

これが終わったらCATSプラグインのOptimizationを開き、Generate Material Listをクリックするとたくさんのテクスチャが開かれます。
Save Atlas To..をクリックするとマテリアルが結合されます。

これが終わったらEye TrackingとVisemesを設定しましょう。
これも表情に関わるところですが、次の画像の通りに設定すればよさそうです。

//image[eye-tracking][Eye Tracking（目の動き）の設定][scale=0.6]{
//}

//image[visemes][Visemes（口の動き）の設定][scale=0.6]{
//}

これが終わったらVRMに出力します。
VRMを保存し終わったらVCCとUnityの世界に帰れます。
