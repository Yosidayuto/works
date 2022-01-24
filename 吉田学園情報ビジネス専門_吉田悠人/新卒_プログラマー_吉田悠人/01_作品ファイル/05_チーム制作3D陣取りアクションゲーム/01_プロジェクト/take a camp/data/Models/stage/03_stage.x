xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 16;
 -1003.29492;18.54880;-227.89560;,
 -713.04169;18.54870;-227.89560;,
 -713.04169;18.54880;-540.56708;,
 -1003.29492;18.54880;-540.56708;,
 708.06781;18.54870;-227.89560;,
 708.06781;18.54880;-540.56708;,
 1003.29492;18.54880;-227.89560;,
 1003.29492;18.54880;-540.56708;,
 -1003.29492;18.54880;236.39960;,
 -713.04169;18.54870;236.39960;,
 708.06781;18.54870;236.39960;,
 1003.29492;18.54880;236.39960;,
 -1003.29492;18.54880;540.56708;,
 -713.04169;18.54880;540.56708;,
 708.06781;18.54880;540.56708;,
 1003.29492;18.54880;540.56708;;
 
 9;
 4;0,1,2,3;,
 4;2,1,4,5;,
 4;5,4,6,7;,
 4;8,9,1,0;,
 4;4,1,9,10;,
 4;6,4,10,11;,
 4;12,13,9,8;,
 4;10,9,13,14;,
 4;11,10,14,15;;
 
 MeshMaterialList {
  1;
  9;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "stage_3.png";
   }
  }
 }
 MeshNormals {
  16;
  0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;;
  9;
  4;8,9,5,2;,
  4;5,9,10,7;,
  4;7,10,11,3;,
  4;12,13,9,8;,
  4;10,9,13,14;,
  4;11,10,14,15;,
  4;0,4,13,12;,
  4;14,13,4,6;,
  4;15,14,6,1;;
 }
 MeshTextureCoords {
  16;
  0.286750;0.000010;,
  0.286780;0.142700;,
  -0.002560;0.142810;,
  -0.002600;0.000120;,
  0.286970;0.854960;,
  -0.002370;0.855060;,
  0.287010;1.002930;,
  -0.002330;1.003030;,
  0.716400;-0.000140;,
  0.716440;0.142540;,
  0.716630;0.854800;,
  0.716670;1.002770;,
  0.997870;-0.000250;,
  0.997910;0.142440;,
  0.998100;0.854700;,
  0.998140;1.002670;;
 }
}
