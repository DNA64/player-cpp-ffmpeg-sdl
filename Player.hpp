#pragma once
#include <iostream>
#include <string>

#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/avutil.h>
#include <libpostproc/postprocess.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>
}
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "avfilter.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "swscale.lib")


#define ERROR_SIZE 128

//define o formato do frame AV_PIX_FMT_RGB24 ou AV_PIX_FMT_YUV480P
#define FORMATO AV_PIX_FMT_RGB24

#include "SDL.h"
#include <SDL_thread.h>     // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono> 

using namespace std;
using namespace cv;


class Player {
public:

	Player(string endereco);
	~Player(void);

	void exibirInformacaoArquivoVideo(void);
	int alocarMemoria(void);
	int lerFramesVideo(void);
	//cria display com STL
	int criarDisplay(void);

private:

	//armazena o �ndice do determinado Stream a ser transmitido
	int videoStream;

	//contem informa��es sobre o arquivo de v�deo, incluindo os codecs, etc
	AVFormatContext *pFormatCtx = NULL;

	//contem informa��es do codec do v�deo, obtidas atraves de
	//pFormatCtx->streams[i]->codecpar
	//olhando o codec_type e vendo se � transmissao de video do tipo AVMEDIA_TYPE_VIDEO
	AVCodecParameters *pCodecParameters = NULL;

	//informa��es do codecParameters, por�m copiadas. o pCodecParameters serve como um backup das informa��es do v�deo
	AVCodecContext *pCodecCtx = NULL;

	//guarda o codec do v�deo
	AVCodec *pCodec = NULL;

	//estrutura que guarda o frame
	AVFrame *pFrame = NULL;

	//estrutura que guarda o frame RGB
	AVFrame *pFrameRGB = NULL;

	//buffer para leitura dos frames
	uint8_t *buffer = NULL;

	//estrutura que armazena a convers�o para RGB
	struct SwsContext *sws_ctx = NULL;

	//surface window para exibir o video
	//pode ter m�ltiplas screens
	SDL_Window *screen;

	SDL_Renderer *renderer;

	SDL_Texture* bmp;
	
	//exibe o erro com rela��o ao seu respectivo c�digo
	void exibirErro(int erro);

	int obterCodecParameters(void);

	int lerCodecVideo(void);

	int salvarFrame(AVFrame *pFrame, int width, int height, int iFrame);
};