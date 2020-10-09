## 目次
* [準備](#準備)<br>
* [プログラムの説明 (Winと後半が異なります)](#プログラムの説明-後半が異なります)<br>
* [課題その1](#課題その1)<br>
* [ディスプレイリスト-(Winと異なります)](#ディスプレイリスト-コードが異なります)<br>
* [移動・回転・拡大縮小（Winと共通）](#移動-回転-拡大縮小)<br>
* [行列のコントロール（Winと共通）](#行列のコントロール)<br>
* [課題その2](#課題その2)
* [課題その3](#課題その3)
* [課題その4](#課題その4)


## 準備
ここのコードをダウンロード、解凍してください。sample.xcodeproj を開き実行すると、中央に白い四角形が現れるはずです。	


## プログラムの説明-後半が異なります
初期化処理については[直線の回](https://github.com/trnciii/cge2020mac/tree/1_lines)を参考にしてください。


### 描画内容
次のdisplay関数では、四角形を描いています。
```cpp
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f( 0.5f, 0.5f);
        glVertex2f( 0.5f,-0.5f);
        glVertex2f(-0.5f,-0.5f);
    glEnd();
}
```
`glColor3f(); `ではこれから描く頂点の色を設定しています。括弧内の値は左から赤、緑、青の強さで、それぞれ0.0～1.0 の値をとります。ここでは全ての値が1 ですので、色は白になります。

`glVertex2f();` は頂点を設定していて、括弧内の数字は点の座標です。
この場合、４つの点が定義されています。 そして、これらをどのようにしてつないでいくかというのが`glBegin();`の括弧内の文字列で示されています。 この場合は`GL_POLYGON`となっていますから、４つの頂点で一枚のポリゴン（面）が作られています。 そして、`glEnd();`で定義を終わります。

#### ▽▲ 図形のタイプ ▲▽

`glBegin();` の括弧内の`GL_POLYGON` 部分を書き換えることにより、図形のタイプを指定することができます。

|タイプ名								|説明										|
|-----------------------------------|-------------------------------------------|
|GL_POINTS							|点を打ちます									|
|GL_LINES							|２点を対にして、その間を直線で結びます。			|
|GL_LINE_STRIP						|折れ線を描きます。								|
|GL_LINE_LOOP						|折れ線を描きます。始点と終点の間も結ばれます。		|
|GL_TRIANGLES / GL_QUADS			|３／４点を組にして、三角形／四角形を描きます。		|
|GL_TRIANGLE_STRIP / GL_QUAD_STRIP	|一辺を共有しながら帯状に三角形／四角形を描きます。	|
|GL_TRIANGLE_FAN					|一辺を共有しながら扇状に三角形を描きます。			|
|GL_POLYGON							|凸多角形を描きます。							|

### 再描画
次の関数は「再描画」のための関数です。ここで視界の設定をしています。以下で説明していない部分に付いては、後の章で説明します。

```cpp
void reshape(GLFWwindow* window, int w, int h)
{
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h );　//ウィンドウ全体をビューポートにする
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);　//視野の指定
}
```
`glOrtho();`では視界の設定をしています。
括弧内左から、ウィンドウ左端、右端、上、下、そして手前、奥の座標を設定し、この範囲内にある物体を描画するようにしています。図にすると下のようになります。<br>
`glOrtho(left, right, bottom, top, near, far);`のとき

![](http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cge2020/img/surface/viewport1.jpg)

この「視野の範囲」は３次元であり、視体積と呼びます。


## 課題その1

あなたのイニシャルを、画面上に描いてください。"MP1”だとイメージとしては下のようなものになります。

![](http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cge2020/img/surface/MP1.gif)

注意事項：
Mのように、へこみ部分のあるポリゴン（凹ポリゴンといいます）や、Pのように、穴のあいたポリゴンは、OpenGLでは綺麗に表示できません。分解して描く・GL_LINE_LOOPなどを使ってラインだけで描くなど工夫してください。

ヒント１：
最終的なイメージを方眼紙のようなものに描いて、図形の座表を紙面上で位置を計算しておくとスムーズに表現できます。

ヒント２：
図形も様々なタイプがあるので、ためしに色々な図形のタイプを使って文字を表現してみましょう。

## ディスプレイリスト-コードが異なります
ディスプレイリストを使うと、図形を描く、などの命令を保存し、それを簡単に呼び出したりすることができます。つまり、一度定義した物体を「使い回す」事ができます。
では まず、プログラムの頭部分に次の黒文字の行を書き加えてください。
```cpp
#define GL_SILENCE_DEPRECATION
#include "GLFW/glfw3.h"
#include <math.h>

#define SQUARE 1
```
`#define` はある文字列を違う文字列に置き換える定義をします。ここでは、「"SQUARE "という文字列を数字の1と等しいとみなす」という処理を行っています。これを"マクロ定義（マクロ置き換え）"と言います。

続いて、`myinit()` の中を次のように書き換えて下さい。
```cpp
void myinit(GLFWwindow** window)
{
    glfwInit();
    *window = glfwCreateWindow(600, 600, "surface", NULL, NULL);
    glfwMakeContextCurrent(*window);
    glClearColor(0, 0, 0, 1);
    
    // ここから追記
    glNewList(SQUARE, GL_COMPILE);

    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f( 0.5f, 0.5f);
        glVertex2f( 0.5f,-0.5f);
        glVertex2f(-0.5f,-0.5f);
    glEnd();

    glEndList();
    // 追記おわり
}
```
`glNewList()` は保存を開始します。 `glEndList()` は保存を終了します。
つまり、この二つの間に書かれた処理を保存することになります。

この場合、“四角を描く”という命令が保存されることになります。
この場合、SQUARE（つまり"1"）に"四角を描く"という命令を保存したことになります。

定義したオブジェクトを使ってみましょう。`display()` の中を次のように書き換えます。
```cpp
void display(void){

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glColor3f(1.0f, 1.0f, 1.0f);
	glCallList(SQUARE);	
	glFlush();
}
```
リストで定義されたオブジェクトの呼び出しには、 `glCallList()` を使います。括弧内（引数）はオブジェクトの名前（整数）が入ります。ここではSQUARE（=1）という名前のオブジェクト＝先ほどリストで定義したオブジェクトを呼び出しています。
実行してみても見かけは変わりません。でも、複雑なオブジェクト（ここでは単なる正方形ですが・・・）を１行の記述で呼び出すことができます。


## 移動 回転 拡大縮小
Windowsと共通です。もとの資料を参考にしてください。

## 行列のコントロール
Windowsと共通です。もとの資料を参考にしてください。

## 課題その2
次のような画面を作ってみて下さい。<br>
![](http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cge2020/img/surface/1_2_var0.gif)

## 課題その3
「課題その２」を変更して、次のような画面を作ってみて下さい。<br>
<img src="http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cge2020/img/surface/ogl1_4.gif" width="300">
<img src="http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cge2020/img/surface/square2.gif" width="300"><br>
<img src="http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cge2020/img/surface/1_2_var1.gif" width="300">
<img src="http://www.design.kyushu-u.ac.jp/~rtsuruno/lectures/cge2020/img/surface/1_2_var2.gif" width="300">


## 課題その4
上記のことを参考にして、自分で面白そうな課題を作って、実現してみてください。 何を作ってもOKです。
