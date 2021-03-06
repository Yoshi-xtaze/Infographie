#include "tgaimage.h"
#include "Point.h"
#include "Matrice.h"
#include "Vecteur.h"
#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <cmath>
#include <algorithm>

# define PI           3.14159265358979323846  /* pi */
using namespace std;
double zbuffer[1000][1000];
int tailleImage = 1000;
int tailleImageSurDeux = tailleImage / 2;
TGAImage imageTexture(tailleImage, tailleImage, TGAImage::RGB);

vector<vector<double> > lectureSommets(string nomFichier) {
	cout << "Lecture des sommets... ";
	ifstream fichier(nomFichier.c_str(), ios::in);
	if (fichier)
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbSommets = 0;
		while (getline(fichier, ligne, '\n'))
		{
			if (ligne[0] == 'v' && ligne[1] == ' ' && ligne[2] == ' ')
			{
				string aux;
				for (unsigned int i = 3; i < ligne.size(); ++i)
				{
					aux.push_back(ligne[i]);
				}
				stringstream ss;
				ss.str(aux);
				double partie1, partie2, partie3;
				ss >> partie1 >> partie2 >> partie3;
				vectLigne.push_back(partie1);
				vectLigne.push_back(partie2);
				vectLigne.push_back(partie3);
				vect.push_back(vectLigne);
				nbSommets++;
			}
			vectLigne.clear();
		}
		cout << "(" << nbSommets << " sommets) ";
		cout << "Succes" << endl;
		return vect;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

vector<vector<double> > lectureTriangles(string nomFichier) {
	cout << "Lecture des triangles... ";
	ifstream fichier(nomFichier.c_str(), ios::in);

	if (fichier)
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbTriangle = 0;
		while (getline(fichier, ligne, '\n'))
		{
			if (ligne[0] == 'f' && ligne[1] == ' ')
			{
				string aux;
				for (unsigned int i = 2; i < ligne.size(); ++i)
				{
					aux.push_back(ligne[i]);
				}
				int posEspace1 = aux.find(' ', 0);
				int posEspace2 = aux.find(' ', posEspace1 + 1);
				string texte1 = aux.substr(0, posEspace1);
				string texte2 = aux.substr(posEspace1 + 1, posEspace2 - (posEspace1 + 1));
				string texte3 = aux.substr(posEspace2 + 1, aux.size() - (posEspace2 + 1));
				int posSlashTexte1 = texte1.find('/', 0);
				int posSlashTexte2 = texte2.find('/', 0);
				int posSlashTexte3 = texte3.find('/', 0);
				double partie1 = atof(texte1.substr(0, posSlashTexte1).c_str());
				double partie2 = atof(texte2.substr(0, posSlashTexte2).c_str());
				double partie3 = atof(texte3.substr(0, posSlashTexte3).c_str());
				vectLigne.push_back(partie1);
				vectLigne.push_back(partie2);
				vectLigne.push_back(partie3);
				vect.push_back(vectLigne);
				nbTriangle++;
			}
			vectLigne.clear();
		}
		cout << "(" << nbTriangle << " triangles) ";
		cout << "Succes" << endl;
		return vect;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

vector<vector<double> > lectureTexturesF(string nomFichier) {
	cout << "Lecture des textures f... ";
	ifstream fichier(nomFichier.c_str(), ios::in);
	if (fichier)
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbTexture = 0;
		while (getline(fichier, ligne, '\n'))
		{
			if (ligne[0] == 'f' && ligne[1] == ' ')
			{
				string aux;
				for (unsigned int i = 2; i < ligne.size(); ++i)
				{
					aux.push_back(ligne[i]);
				}
				int posEspace1 = aux.find(' ', 0);
				int posEspace2 = aux.find(' ', posEspace1 + 1);
				string texte1 = aux.substr(0, posEspace1);
				string texte2 = aux.substr(posEspace1 + 1, posEspace2 - (posEspace1 + 1));
				string texte3 = aux.substr(posEspace2 + 1, aux.size() - (posEspace2 + 1));
				int posSlash1Texte1 = texte1.find('/', 0);
				int posSlash1Texte2 = texte2.find('/', 0);
				int posSlash1Texte3 = texte3.find('/', 0);
				int posSlash2Texte1 = texte1.find('/', posSlash1Texte1 + 1);
				int posSlash2Texte2 = texte2.find('/', posSlash1Texte2 + 1);
				int posSlash2Texte3 = texte3.find('/', posSlash1Texte3 + 1);
				int partie1 = atoi(texte1.substr(posSlash1Texte1 + 1, posSlash2Texte1 - 1 - posSlash1Texte1).c_str());
				int partie2 = atoi(texte2.substr(posSlash1Texte2 + 1, posSlash2Texte2 - 1 - posSlash1Texte2).c_str());
				int partie3 = atoi(texte3.substr(posSlash1Texte3 + 1, posSlash2Texte3 - 1 - posSlash1Texte3).c_str());
				vectLigne.push_back(partie1);
				vectLigne.push_back(partie2);
				vectLigne.push_back(partie3);
				vect.push_back(vectLigne);
				nbTexture++;
			}
			vectLigne.clear();
		}
		cout << "(" << nbTexture << " textures f) ";
		cout << "Succes" << endl;
		return vect;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

vector<vector<double> > lectureTexturesVt(string nomFichier) {
	cout << "Lecture des textures vt... ";
	ifstream fichier(nomFichier.c_str(), ios::in);
	if (fichier)
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbTexture = 0;
		while (getline(fichier, ligne, '\n'))
		{
			if (ligne[0] == 'v' && ligne[1] == 't' && ligne[2] == ' ' && ligne[3] == ' ')
			{
				string aux;
				for (unsigned int i = 4; i < ligne.size(); ++i)
				{
					aux.push_back(ligne[i]);
				}
				stringstream ss;
				ss.str(aux);
				double partie1, partie2;
				ss >> partie1 >> partie2;
				vectLigne.push_back(partie1);
				vectLigne.push_back(partie2);
				vect.push_back(vectLigne);
				nbTexture++;
			}
			vectLigne.clear();
		}
		cout << "(" << nbTexture << " textures vt) ";
		cout << "Succes" << endl;
		return vect;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

double maxDeux(double a, double b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}

double maxTrois(double a, double b, double c) {
	return maxDeux(maxDeux(a, b), c);
}

double minDeux(double a, double b) {
	if (a <= b) {
		return a;
	}
	else {
		return b;
	}
}

double minTrois(double a, double b, double c) {
	return minDeux(minDeux(a, b), c);
}

void initialisationZBuffer() {
	for (int i = 0; i<1000; i++) {
		for (int j = 0; j<1000; j++) {
			zbuffer[i][j] = std::numeric_limits<int>::min();
		}
	}
}

void boiteEnglobante(Point &a, Point &b, Point &c, Matrice &boite) {
	/* Boite englobante minAbs, minOrd, maxAbs, maxOrd */	
	boite(0, 0) = minTrois(a.x, b.x, c.x);
	boite(1, 0) = minTrois(a.y, b.y, c.y);
	boite(2, 0) = maxTrois(a.x, b.x, c.x);
	boite(3, 0) = maxTrois(a.y, b.y, c.y);

	/* Pour ne pas �tre out of map */
	boite(0,0) = max(0., boite(0,0));
	boite(1,0) = max(0., boite(1,0));
	boite(2,0) = min(boite(2,0), (double)tailleImage);
	boite(3,0) = min(boite(3,0), (double)tailleImage);
}

void recuperationTriangle(vector<vector<double> > &vectPoints, int ligne1, int ligne2, int ligne3, Matrice &transformation, Point &a, Point &b, Point &c) {
	Matrice A(4, 1);
	Matrice B(4, 1);
	Matrice C(4, 1);
	Matrice aux(4, 1);
	A(0, 0) = vectPoints[ligne1 - 1][0];
	A(1, 0) = vectPoints[ligne1 - 1][1];
	A(2, 0) = vectPoints[ligne1 - 1][2];
	A(3, 0) = 1;
	aux = transformation*A;
	a = Point(aux(0, 0) / aux(3, 0), aux(1, 0) / aux(3, 0), aux(2, 0) / aux(3, 0));
	B(0, 0) = vectPoints[ligne2 - 1][0];
	B(1, 0) = vectPoints[ligne2 - 1][1];
	B(2, 0) = vectPoints[ligne2 - 1][2];
	B(3, 0) = 1;
	aux = transformation*B;
	b = Point(aux(0, 0) / aux(3, 0), aux(1, 0) / aux(3, 0), aux(2, 0) / aux(3, 0));
	C(0, 0) = vectPoints[ligne3 - 1][0];
	C(1, 0) = vectPoints[ligne3 - 1][1];
	C(2, 0) = vectPoints[ligne3 - 1][2];
	C(3, 0) = 1;
	aux = transformation*C;
	c = Point(aux(0, 0) / aux(3, 0), aux(1, 0) / aux(3, 0), aux(2, 0) / aux(3, 0));
}

void recuperationTexture(vector<vector<double> > &vectTexturesVt, int fTextureA, int fTextureB, int fTextureC, Matrice &vt) {
	vt(0, 0) = vectTexturesVt[fTextureA - 1][0];
	vt(1, 0) = vectTexturesVt[fTextureA - 1][1];
	vt(0, 1) = vectTexturesVt[fTextureB - 1][0];
	vt(1, 1) = vectTexturesVt[fTextureB - 1][1];
	vt(0, 2) = vectTexturesVt[fTextureC - 1][0];
	vt(1, 2) = vectTexturesVt[fTextureC - 1][1];
}

double calculCoefficiant(Point &a, Point &b, Point &c) {
	double denominateur = (((b.x - a.x)*(c.y - a.y)) - ((c.x - a.x)*(b.y - a.y)));
	double coeff = 1. / denominateur;
	return coeff;
}

bool appartientTriangle(Point &a, Point &b, Point &c, Point &p, double coeff, double &u, double &v, double &w) {
	u = (coeff*(c.y - a.y))*(p.x - a.x) + (coeff*(a.x - c.x))*(p.y - a.y);
	v = (coeff*(a.y - b.y))*(p.x - a.x) + (coeff*(b.x - a.x))*(p.y - a.y);
	w = 1 - u - v;
	if (u < -1e-5 || v < -1e-5 || w < -1e-5) {
		return false;
	}
	else {
		return true;
	}
}

void negatif(TGAColor &color) {
	color.r = 255 - color.r;
	color.g = 255 - color.g;
	color.b = 255 - color.b;
}

double tonalite(double i) {
	return (3 * pow((i / 256), 2) - 2 * pow((i / 256), 3)) * 256;
}

void contraste(TGAColor &color) {
	color.r = tonalite(color.r);
	color.g = tonalite(color.g);
	color.b = tonalite(color.b);
}

void dessinePixel(Matrice &vt, Point &p, Vecteur &lumiere, Matrice &filtre, double &u, double &v, double &w, TGAImage &africanDiffuse, TGAImage &africanNM, TGAImage &africanSpecular) {
	zbuffer[(int)p.x][(int)p.y] = p.z;
	double pix_x = (vt(0, 0)*w + vt(0, 1)*u + vt(0, 2)*v) * africanDiffuse.get_width();
	double pix_y = (vt(1, 0)*w + vt(1, 1)*u + vt(1, 2)*v) * africanDiffuse.get_height();
	TGAColor colorPix = africanDiffuse.get((int)pix_x, (int)pix_y);
	TGAColor colorNm = africanNM.get((int)pix_x, (int)pix_y);
	Vecteur normalPix = Vecteur(colorNm.r, colorNm.g, colorNm.b);
	normalPix.normaliser();
	double produitScalaire = 2 * normalPix.produitVectoriel(lumiere);
	Vecteur r = Vecteur((normalPix.x * produitScalaire) - lumiere.x, (normalPix.y * produitScalaire) - lumiere.y, (normalPix.z * produitScalaire) - lumiere.z);
	r.normaliser();
	TGAColor colorSpec = africanSpecular.get((int)pix_x, (int)pix_y);
	double spec = pow(max(r.z, 0.), colorSpec.b);
	double intensity = max(0., normalPix.x*lumiere.x + normalPix.y*lumiere.y + normalPix.z*lumiere.z);
	Matrice couleur(4, 1);
	couleur(0, 0) = min(5 + colorPix.r*(intensity + 0.6*spec), 255.);
	couleur(1, 0) = min(5 + colorPix.g*(intensity + 0.6*spec), 255.);
	couleur(2, 0) = min(5 + colorPix.b*(intensity + 0.6*spec), 255.);
	couleur(3, 0) = min(5 + colorPix.a*(intensity + 0.6*spec), 255.);
	couleur = filtre*couleur;
	TGAColor color = TGAColor(min(couleur(0, 0), 255.), min(couleur(1, 0), 255.), min(couleur(2, 0), 255.), min(couleur(3, 0), 255.));
	//negatif(color);
	//contraste(color);
	imageTexture.set((int)p.x, (int)p.y, color);
}

void lectureTGAImage(TGAImage &africanDiffuse, TGAImage &africanNM, TGAImage &africanSpecular) {
	africanDiffuse.read_tga_file("african_head_diffuse.tga");
	africanDiffuse.flip_vertically();
	africanNM.read_tga_file("african_head_nm.tga");
	africanNM.flip_vertically();
	africanSpecular.read_tga_file("african_head_spec.tga");
	africanSpecular.flip_vertically();
}

void faceTexture(vector<vector<double> > &vectPoints, vector<vector<double> > &vectTriangles, vector<vector<double> > &vectTexturesF, vector<vector<double> > &vectTexturesVt, Matrice &transformation, Matrice &filtre, string nomImage) {
	cout << "Creation image texture... ";
	TGAImage africanDiffuse, africanNM, africanSpecular;
	lectureTGAImage(africanDiffuse, africanNM, africanSpecular);
	double coeff, u, v, w, intensity, produitScalaire, spec;
	Point a, b, c, p;
	Matrice boite = Matrice(4, 1);
	Matrice vt = Matrice(2, 3);
	Vecteur lumiere = Vecteur(1, 1, 0);
	lumiere.normaliser();
	initialisationZBuffer();
	for (unsigned int i = 0; i < vectTriangles.size(); ++i) {
		recuperationTriangle(vectPoints, vectTriangles[i][0], vectTriangles[i][1], vectTriangles[i][2], transformation, a, b, c);
		boiteEnglobante(a, b, c, boite);
		recuperationTexture(vectTexturesVt, vectTexturesF[i][0], vectTexturesF[i][1], vectTexturesF[i][2], vt);
		coeff = calculCoefficiant(a, b, c);
		for (int i = (int)boite(1,0); i <= (int)boite(3,0); i++) {
			for (int j = (int)boite(0,0); j <= (int)boite(2,0); j++) {
				p.x = j;
				p.y = i;
				if (!appartientTriangle(a,b,c,p,coeff,u,v,w)) {
				}
				else {
					p.z = w*a.z + u*b.z + v*c.z;
					if (zbuffer[(int)p.x][(int)p.y] > p.z) {
						continue;
					}
					else {
						dessinePixel(vt,p,lumiere,filtre,u,v,w,africanDiffuse,africanNM,africanSpecular);
					}
				}
			}
		}
	}
	imageTexture.flip_vertically();
	nomImage = nomImage + ".tga";
	const char *nom = nomImage.c_str();
	imageTexture.write_tga_file(nom);
	cout << "Succes" << endl;
}

void anaglyphe(vector<vector<double> > &vectPoints, vector<vector<double> > &vectTriangles, vector<vector<double> > &vectTexturesF, vector<vector<double> > &vectTexturesVt, Matrice &transformation, Matrice &filtre) {
	string image1 = "image1";
	string image2 = "image2";
	imageTexture.clear();
	faceTexture(vectPoints, vectTriangles, vectTexturesF, vectTexturesVt, transformation, filtre, image1);
	double angleY = -2 * (PI) / 180;
	Matrice rotationY = Matrice(4, 4);
	rotationY(0, 0) = cos(angleY);
	rotationY(0, 2) = sin(angleY);
	rotationY(1, 1) = 1;
	rotationY(2, 0) = -sin(angleY);
	rotationY(2, 2) = cos(angleY);
	rotationY(3, 3) = 1;
	transformation =  rotationY * transformation;
	imageTexture.clear();
	faceTexture(vectPoints, vectTriangles, vectTexturesF, vectTexturesVt, transformation, filtre, image2);
	TGAImage img1, img2;
	img1.read_tga_file("image1.tga");
	img1.flip_vertically();
	img2.read_tga_file("image2.tga");
	img2.flip_vertically();
	TGAImage anaglyphe(tailleImage, tailleImage, TGAImage::RGB);
	TGAColor color;
	for (int i = 0; i < tailleImage; i++) {
		for (int j = 0; j < tailleImage; j++) {
			color.r = img1.get(i, j).r;
			color.g = img2.get(i, j).g;
			color.b = img2.get(i, j).b;
			anaglyphe.set(i, j, color);
		}
	}
	anaglyphe.flip_vertically();
	anaglyphe.write_tga_file("anaglyphe.tga");
}

void reflet(vector<vector<double> > &vectPoints, vector<vector<double> > &vectTriangles, vector<vector<double> > &vectTexturesF, vector<vector<double> > &vectTexturesVt, int angle, Matrice &filtre) {
	imageTexture.clear();
	TGAImage finalMiroir(tailleImage, tailleImage, TGAImage::RGB);
	string miroir = "miroir";
	Matrice viewPort = Matrice(4, 4);
	Matrice rotationY = Matrice(4, 4);
	Matrice transformation = Matrice(4, 4);
	double angleY = (-180 + angle) * (PI) / 180;
	rotationY(0, 0) = cos(angleY);
	rotationY(0, 2) = sin(angleY);
	rotationY(1, 1) = 1;
	rotationY(2, 0) = -sin(angleY);
	rotationY(2, 2) = cos(angleY);
	rotationY(3, 3) = 1;
	viewPort(0, 0) = viewPort(1, 1) = viewPort(2, 2) = tailleImageSurDeux;
	viewPort(1, 3) = viewPort(2, 3) = tailleImageSurDeux;
	viewPort(0, 3) = tailleImageSurDeux+100;
	viewPort(3, 3) = 1;
	transformation = viewPort * rotationY;
	faceTexture(vectPoints, vectTriangles, vectTexturesF, vectTexturesVt, transformation, filtre, miroir);
	
	viewPort(0, 0) = viewPort(0, 3) = viewPort(1, 1) = viewPort(2, 2) = viewPort(2, 3) = tailleImageSurDeux/2;
	viewPort(1, 3) = tailleImageSurDeux / 4;
	viewPort(3, 3) = 1;
	angleY = angle * (PI) / 180;
	rotationY(0, 0) = cos(angleY);
	rotationY(0, 2) = sin(angleY);
	rotationY(1, 1) = 1;
	rotationY(2, 0) = -sin(angleY);
	rotationY(2, 2) = cos(angleY);
	rotationY(3, 3) = 1;
	transformation = viewPort * rotationY;
	imageTexture.flip_vertically();
	faceTexture(vectPoints, vectTriangles, vectTexturesF, vectTexturesVt, transformation, filtre, miroir);	
}

int main(int argc, char** argv)
{
	cout << "Projet d'infographie - M1 Informatique" << endl;
	/* Parse du fichier obj */
	vector<vector<double> > vectPoints = lectureSommets("african_head.obj");
	vector<vector<double> > vectTriangles = lectureTriangles("african_head.obj");
	vector<vector<double> > vectTexturesF = lectureTexturesF("african_head.obj");
	vector<vector<double> > vectTexturesVt = lectureTexturesVt("african_head.obj");
	/* Creation du Viewport */
	Matrice viewPort = Matrice(4, 4);
	viewPort(0, 0) = viewPort(0, 3) = viewPort(1, 1) = viewPort(1, 3) = viewPort(2, 2) = viewPort(2, 3) = tailleImageSurDeux;
	viewPort(3, 3) = 1;
	/* Cr�ation du zoom */
	Matrice zoom = Matrice(4, 4);
	double zoomAction = 0.8;
	zoom(0, 0) = zoom(1, 1) = zoom(2, 2) = zoomAction;
	zoom(3, 3) = 1;
	/* Cr�ation de la Persective */
	double c = 10000;
	Matrice perspective = Matrice(4, 4);
	perspective(0, 0) = perspective(1, 1) = perspective(2, 2) = perspective(3, 3) = 1;
	perspective(3, 2) = -1 / c;
	/* Cr�ation de la Rotation autour de l'axe y */
	double angleY = 0 * (PI) / 180;
	Matrice rotationY = Matrice(4, 4);
	rotationY(0, 0) = cos(angleY);
	rotationY(0, 2) = sin(angleY);
	rotationY(1, 1) = 1;
	rotationY(2, 0) = -sin(angleY);
	rotationY(2, 2) = cos(angleY);
	rotationY(3, 3) = 1;
	/* Cr�ation de la rotation autour de l'axe x */
	double angleX = 0 * (PI) / 180;
	Matrice rotationX = Matrice(4, 4);
	rotationX(0, 0) = 1;
	rotationX(1, 1) = cos(angleX);
	rotationX(1, 2) = -sin(angleX);
	rotationX(2, 1) = sin(angleX);
	rotationX(2, 2) = cos(angleX);
	rotationX(3, 3) = 1;
	/* Cr�ation de la rotation autour de l'axe z */
	double angleZ = 0 * (PI) / 180;
	Matrice rotationZ = Matrice(4, 4);
	rotationZ(0, 0) = cos(angleZ);
	rotationZ(0, 1) = -sin(angleZ);
	rotationZ(1, 0) = sin(angleZ);
	rotationZ(1, 1) = cos(angleZ);
	rotationZ(2, 2) = 1;
	rotationZ(3, 3) = 1;
	/* Creation matrice couleur */
	Matrice sepia = Matrice(4, 4);
	sepia(0, 0) = .393;
	sepia(0, 1) = .769;
	sepia(0, 2) = .189;
	sepia(1, 0) = .349;
	sepia(1, 1) = .686;
	sepia(1, 2) = .168;
	sepia(2, 0) = .272;
	sepia(2, 1) = .534;
	sepia(2, 2) = .131;
	sepia(3, 3) = 1;
	/* Creation matrice nuance de gris */
	Matrice nuanceGris = Matrice(4, 4);
	nuanceGris(0, 0) = nuanceGris(0, 1) = nuanceGris(0, 2) = nuanceGris(1, 0) = nuanceGris(1, 1) = nuanceGris(1, 2) = nuanceGris(2, 0) = nuanceGris(2, 1) = nuanceGris(2, 2) = 1 / 3.;
	nuanceGris(3, 3) = 1;
	/* Creation matrice identite */
	Matrice identite = Matrice(4, 4);
	identite(0, 0) = identite(1, 1) = identite(2, 2) = identite(3, 3) = 1;
	/* Creation matrice miroir */
	Matrice miroir = Matrice(identite);
	miroir(0, 0) = -1;
	/* Creation matrice filtre rouge */
	Matrice filtreRouge = Matrice(4, 4);
	filtreRouge(0, 0) = filtreRouge(3, 3) = 1;
	/* Creation matrice filtre cyan */
	Matrice filtreCyan = Matrice(4, 4);
	filtreCyan(1, 1) = filtreCyan(2, 2) = filtreCyan(3, 3) = 1;
	/* Creation de la rotation complete */
	Matrice transformation = Matrice(4, 4);
	transformation = viewPort*perspective*rotationX*rotationY*rotationZ*zoom;
	/* On dessine l'image */
	faceTexture(vectPoints, vectTriangles, vectTexturesF, vectTexturesVt, transformation, identite, "imageTexture");
	//anaglyphe(vectPoints, vectTriangles, vectTexturesF, vectTexturesVt, transformation, identite);
	//reflet(vectPoints, vectTriangles, vectTexturesF, vectTexturesVt, 155, identite);
	//system("PAUSE");
	return 0;
}