= 髪のボーンを減らそう

== 髪のボーンが多ければ重くなる

VRoidアバターに限らず、VRChatのアバターの髪の揺れに関してはボーンを使って揺らしています。
ボーンが多くなると表示が重くなり、ランクが下がってしまうのでボーンを減らすことは至上命題です。
その解決策としては髪のボーンを減らすことなのですが、ボーンを減らしてしまうと揺れが不自然になってしまいます。
なので、ボーンが少なくても揺れに影響しないショートヘアを採用するのは一つの最適解といえます。
Fallbackアバターを目指す場合、ショートヘアにした上でこれから紹介する方法を使ってボーンを減らしておくとよいでしょう。

しかし、ロングヘアにこだわりのある方もいると思います。
ロングヘアは、必然的にボーンが多くなります。
髪の揺れを諦めれば、ロングヘアにするという選択肢も採れます。
しかし、揺れる髪もなかなか美しいもので……。
なので、すべきことは髪のボーンを減らすことなのです。

髪のボーンを減らすことはVRM出力時にもできるのですが、その場合は髪が不自然になってしまうこともよくあります。
なら、髪のボーンを不自然にならない程度に削ればよいのです。
その設定は、髪型の所から「髪の揺れ方を設定」することでできます。

== 私の設定例

デフォルトのPC版では、このように髪の揺れ方が設定されています。

//image[pc-maegami][PC版の前髪設定][scale=0.6]{
//}

//image[pc-ushirogami][PC版の後ろ設定][scale=0.6]{
//}

私のAndroid版では、前髪は2つのグループに、後ろ髪は1つのグループにまとめています。

//image[android-maegami][PC版の前髪設定][scale=0.6]{
//}

//image[android-ushirogami][PC版の後ろ設定][scale=0.6]{
//}

これらの設定は、ボーンのグループ数を減らすことで設定できます。
こうするとボーンが減り、Androidにも優しいアバターに近付きます。
