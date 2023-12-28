= VCCで設定しよう

この次はVCCの設定です。Windowsの場合、GUI版が使えます。
また、Macの場合はコマンドラインで操作することになりますが、Windowsでもコマンドラインで操作することは可能です。
私はMacで改変することが多いのでコマンドラインを使うことが多いですが、GUI版の方が直感的なのでお好みで、というところです。

== WindowsでVCCを使うには

まずすべきは、リポジトリの追加です。
VCCはリポジトリからパッケージをインストールすることができますが、ここでリポジトリを設定しておくとUnityでポチポチする手間が省けます。
それで、新規アバタープロジェクトを作成したら必要なパッケージを追加してUnityを開くだけと簡単です。

なお、テンプレートを作ることも可能なので、このパッケージを入れた状態でプロジェクトを作っておきたいという場合は作っておいた方がよいでしょう。

ただし、パッケージのバージョンアップはそれぞれ手動で行わなければいけません。
一応、このパッケージのバージョンを上げるには他のパッケージのバージョンも上げなければいけないというケースではいっしょにバージョンを上げてくれます。
後述するコマンドラインからの方法では問答無用に最新版になってしまうので、バグを踏むのが怖いという人は手動でポチポチあげていってもよいと思います。

== コマンドラインでVCCを使うには

実はVCCにはコマンドラインインターフェースがあります。
コマンドラインインターフェースとなるととっつきにくい印象がありますが、一度スクリプトを設定してくれるとインストールするアセットを一発で設定できるので使いやすいです。
まずは、.NET 6系をインストールします。これはVCCのコマンドラインインターフェースを使うのに必要です。
なお、別のバージョンの.NETがインストールされている場合、VCCのコマンドラインインターフェースに失敗します。
その場合は、.NET 6をインストールした上で以下のような.NETのバージョンを指定するファイルをホームフォルダに配置すると、全てのフォルダで指定したバージョンの.NETが使われます。

//source[global.json]{
{
  "sdk": {
    "version": "6.0.408"
  }
}
//}

.NET 6をインストールしたら、次のコマンドを入力してVCCのコマンドラインインターフェースをインストールしましょう。
ここからの内容はビデカメさんの記事に従います。

//cmd{
> @<b>{dotnet tool install --global vrchat.vpm.cli}
//}

正常にインストールできたらまずはバージョンの確認です。
次のコマンドを実行しましょう。

//cmd{
> @<b>{vpm --version}
//}

なお、アップデートは次のコマンドでできます。

//cmd{
> @<b>{dotnet tool update --global vrchat.vpm.cli}
//}

次に、テンプレートをインストールします。次のコマンドを実行してください。

//cmd{
> @<b>{vpm install templates}
//}

インストールに成功したか確かめるために、インストールされたテンプレートのリストを確認するのも忘れずに。

//cmd{
> @<b>{vpm list templates}
//}

そして、このコマンドを実行してUnity Hubが認識されているか確認しましょう。

//cmd{
> @<b>{vpm check hub}
//}

同様に、Unityも。

//cmd{
> @<b>{vpm check unity}
//}

ここが終わったら、プロジェクトで使うリポジトリを追加しておきます。

//cmd{
> @<b>{vpm add repo <リポジトリのパス>}
//}

追加するリポジトリに関してですが、私は以下のリポジトリを入れています。

 * https://vpm.nadena.dev/vpm.json
 * https://mimyquality.github.io/VPM-Repository/index.json
 * https://d4rkc0d3r.github.io/vpm-repos/main.json
 * https://vpm.anatawa12.com/vpm.json
 * https://kurotu.github.io/vpm-repos/vpm.json
 * https://lilxyzw.github.io/vpm-repos/vpm.json
 * https://meronmks.github.io/vpm-repos/vpm.json
 * https://vpm.nekomimi.studio/index.json
 * https://esperecyan.github.io/VRMConverterForVRChat/registry.json
 * https://whiteflare.github.io/vpm-repos/vpm.json
 * https://vpm.ureishi.net/repos.json
 * https://mmmaellon.github.io/MMMaellonVCCListing/index.json
 * https://vpm.rerac.dev/index.json
 * https://suzuryg.github.io/vpm-repos/vpm.json
 * https://vpm.narazaka.net/index.json
 * https://www.negura-karasu.net/vpm/

ここまでリポジトリの設定が終わったら、これらのリポジトリを一発で設定しましょう。
ファイル名は「vpm-install.ps1」として、以下の内容をコピペしておきましょう。
このスクリプトを実行すれば指定した全てのパッケージがインストールされます。
パッケージのバージョンアップも、このスクリプトを再度実行すると全て更新してくれます。
なので、いちいちVCCでそれぞれのパッケージのバージョンアップを手動でしなくても済むのです。

//source[vpm-install.ps1]{
#!/usr/local/microsoft/powershell/7/pwsh

vpm add package com.vrchat.core.vpm-resolver && `
vpm add package com.vrchat.base && `
vpm add package com.vrchat.avatars && `
vpm add package dev.vrlabs.av3manager && `
vpm add package vrchat.blackstartx.gesture-manager && `
vpm add package vrchat.jordo.easyquestswitch && `
vpm add package jp.lilxyzw.liltoon && `
vpm add package jp.lilxyzw.avatar-utils && `
vpm add package nadena.dev.modular-avatar && `
vpm add package com.anatawa12.avatar-optimizer && `
vpm add package jp.pokemori.vrm-converter-for-vrchat && `
vpm add package com.github.kurotu.vrc-quest-tools && `
vpm add package jp.whiteflare.avatartools && `
vpm add package yagihata.radialinventorysystem.v4 && `
vpm add package net.narazaka.vrchat.avatar-menu-creater-for-ma && `
vpm add package net.narazaka.vrchat.manual-baker && `
vpm add package jp.suzuryg.face-emo && `
vpm add package jp.whiteflare.unlitwf && `
vpm check project
//}

なおこちらのスクリプトは https://gist.github.com/huideyeren/994e378a89f181a29b8f432768e0db6f にありますので、適時ダウンロードして使ってください。
また、MacやLinux環境ではpwshという、WindowsのPowerShellを移植したものがありますのでそちらも併せてインストールしてください。

スクリプトの中でインストールするパッケージのリストは以下の通りです。
なお、このリストの中にはメタカル最前線の記事@<bib>{metacul}で指定されている有用なツールが全て含まれています。
このリストはスクリプトで指定されている順に並べられています。

 * VPM Resolver
 * VRChat SDK Base
 * VRChat SDK Avatar
 * Avatar 3.0 Manager
 * Gesture Manager
 * Easy Quest Switch
 * lilToon
 * lilToon Avatar Utility
 * Modular Avatar
 * Avatar Optimizer
 * VRM Converter for VRChat
 * VRCQuestTools
 * AvatarTools
 * Radial Inventory System V4
 * Avatar Menu Creator for Modular Avatar
 * Manual Baker
 * FaceEmo
 * UnlitWF_Shader

そして、Macの方に朗報です。
PowerShellはMac用もあるのでPowerShellをインストールすればなんとMacでも動きます。
これを使えば、必要なパッケージが一発で入るという仕組みなのです。

ここでlilToonなどPC側でしか使わないアセットを入れているのに疑問を感じた方もいるかもしれません。
その理由は、PC版とUnityプロジェクトを共存させると手っ取り早く作りやすいからです。
詳しくはこのあとに記載します。
