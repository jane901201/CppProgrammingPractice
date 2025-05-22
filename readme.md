 作品名　　：C++ProgrammingPractice
 Work Name
 作成期間　：最近
 Time Frame

-----------------------------------------------------------------------------
 プログラム作品の開発環境についてご記入ください
 What was the development environment used for your program?
-----------------------------------------------------------------------------
・動作確認したOS名とそのバージョン
  Used OS
  　Windows / MacOS / Android / iOS / Linux ...
    例)Ex: Windows 7 Professional SP1 64bit

Windows 11 Home

・開発に使用したライブラリ、ミドルウェアとそのバージョン
  Used Library/Middleware
  　DirectX / Open GL / PhysX /
  　例)Ex: DirectX 9.0c(Jun 10)

OpenGL

・開発に使用したエンジンのバージョン
  Used Engine
  　Unity / Unreal Engine / Cocos2d-X ...
  　例)Ex: Unity 4.5.2

SDLを使って自作ゲームエンジンを開発しています。

・開発に使用した開発環境のバージョン
  Used Development Environment
  　Visual Studio / Xcode / Android SDK / Java SDK / XNA...
  　例)Ex: Visual Studio 2010 Professional  Version 10.0.40219.1 SP1Rel

Visual Studio Community 2019 Version 16.11.46

-----------------------------------------------------------------------------
 どうしてそのプログラムを作ろうと思いましたか？
 Why did you create this program?
-----------------------------------------------------------------------------
C++でより低レイヤーのゲームエンジンの内容を実装する練習をしたいと考えています。
可能であれば、シェーダーの実装にも挑戦してみたいです。

-----------------------------------------------------------------------------
 プログラムを作成する上で注意した事は？
 What were you careful about?
-----------------------------------------------------------------------------
単一のクラスに過度な責任を持たせないようにするため、そのクラスが独立したクラスとして
分けられる機能を持っていると気づいた時点で、リファクタリングを開始します。
まずは機能を新しいクラスに移し、元のコードをコメントアウトして、新しいコードが正常に
動作することを確認した後、古いコードを削除しています。

-----------------------------------------------------------------------------
 プログラムを作成する上で大変だった所は？
 What did you find difficult?
-----------------------------------------------------------------------------
もともとは SDL_Renderer を使用していましたが、今後シェーダーなどの実装にも挑戦したい
と思い、OpenGL に切り替えることにしました。
この過程で、OpenGL は描画処理においてより多くの設定が必要なため、画面が正しく表示され
ない原因を確認するのにかなりの時間を費やしましたが、最終的に無事に画面を表示させること
ができ、大きな達成感がありました。

-----------------------------------------------------------------------------
 力をいれて作った部分で、「プログラム上」で特に注意してみてもらいたい所は？
 What points do you want us particulary focus on your work?
-----------------------------------------------------------------------------
より低レイヤーのプログラムを実装したことで、多くの基礎的な機能を自分で作る必要があり
ました。
そのため、コードが煩雑にならないように、画像などのアセットをフォルダで分類し、プログ
ラム全体の可読性を高めるようにしています。


-----------------------------------------------------------------------------
 参考にしたソースファイルがあるのなら、 どの様なところを参考にしましたか？
 またその部分のファイル名を書いてください。
 If you took some source codes as reference, what part of them did you use? 
 Please also tell us the filename of that part.
-----------------------------------------------------------------------------
ゲームプログラミングC++
クラスや変数の命名規則、およびコード全体の構成の参考。

※ 注意 - Note - ※
他の人が作成したライブラリ、関数等を使っている場合は、
その部分を「別ファイル」に分けて、そのファイル名を書いてください。
If you are using a library or function created by someone else,
please put those parts in a separeted file and write the corresponding filename.

 ＜以下のような場合が該当します＞
　*　他人の作った関数を使用した場合
　*　何かを参考にし参考元のソースが半分以上残っている場合
　*　フリーのライブラリを使用した場合（ライブラリ名を明記してください。）
　*　他人の作ったライブラリを使用した場合（ライブラリ名を明記してください。）
　*　「チーム」で作成した作品の場合
　　（自分の担当した箇所やソースファイル名がわかるよう明記してください。）
For example:
　*　If you use a function made by others
　*　If you take something in reference and the referenced source represent more than half
　*　If you use a free library (please write the library name)
　*　If you use a library made by others (please write the library name)
　*　If the work is made in a team
     (please describe the source file name and points that you were in charge of)