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
 39;
 -0.24384;-1.42530;-0.24378;,
 -0.32914;-0.87060;-0.32908;,
 -0.00004;-0.87060;-0.43878;,
 -0.00004;-1.61940;-0.32908;,
 0.32906;-0.87060;-0.32908;,
 0.24376;-1.42530;-0.24378;,
 -0.00004;-0.12170;-0.32908;,
 0.24376;-0.31590;-0.24378;,
 -0.24384;-0.31590;-0.24378;,
 -0.32914;-0.12170;0.00002;,
 -0.00004;-0.00010;0.00002;,
 0.32906;-0.12170;0.00002;,
 -0.00004;-0.12170;0.32912;,
 0.24376;-0.31590;0.24382;,
 -0.24384;-0.31590;0.24382;,
 -0.32914;-0.87060;0.32912;,
 -0.00004;-0.87060;0.43882;,
 0.32906;-0.87060;0.32912;,
 -0.00004;-1.61940;0.32912;,
 0.24376;-1.42530;0.24382;,
 -0.24384;-1.42530;0.24382;,
 -0.32914;-1.61940;0.00002;,
 -0.00004;-1.74100;0.00002;,
 0.32906;-1.61940;0.00002;,
 -0.00004;-1.61940;-0.32908;,
 0.24376;-1.42530;-0.24378;,
 -0.24384;-1.42530;-0.24378;,
 0.43886;-0.87060;0.00002;,
 0.32906;-1.61940;0.00002;,
 0.32906;-0.87060;0.32912;,
 0.24376;-1.42530;0.24382;,
 0.32906;-0.12170;0.00002;,
 0.24376;-0.31590;0.24382;,
 -0.24384;-1.42530;0.24382;,
 -0.32914;-0.87060;0.32912;,
 -0.43884;-0.87060;0.00002;,
 -0.32914;-1.61940;0.00002;,
 -0.32914;-0.12170;0.00002;,
 -0.24384;-0.31590;0.24382;;
 
 24;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;2,6,7,4;,
 4;1,8,6,2;,
 4;8,9,10,6;,
 4;6,10,11,7;,
 4;10,12,13,11;,
 4;9,14,12,10;,
 4;14,15,16,12;,
 4;12,16,17,13;,
 4;16,18,19,17;,
 4;15,20,18,16;,
 4;20,21,22,18;,
 4;18,22,23,19;,
 4;22,24,25,23;,
 4;21,26,24,22;,
 4;5,4,27,28;,
 4;28,27,29,30;,
 4;27,31,32,29;,
 4;4,7,31,27;,
 4;33,34,35,36;,
 4;36,35,1,0;,
 4;35,37,8,1;,
 4;34,38,37,35;;
 
 MeshMaterialList {
  8;
  24;
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "head.png";
   }
  }
  Material {
   0.081600;0.016000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.760000;0.448000;0.224000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.241600;0.106400;0.000000;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.568000;0.336000;0.168000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  28;
  -0.650481;-0.392108;-0.650481;,
  0.650434;-0.392122;-0.650520;,
  -0.650499;0.392051;-0.650498;,
  0.650451;0.392064;-0.650538;,
  -0.650498;0.392051;0.650499;,
  0.650451;0.392064;0.650538;,
  -0.650481;-0.392108;0.650481;,
  0.650433;-0.392121;0.650521;,
  -0.840437;0.541910;0.000000;,
  0.707042;-0.000006;0.707172;,
  0.000000;-0.541980;0.840391;,
  -0.707106;-0.000006;0.707107;,
  0.840359;-0.542030;0.000000;,
  -0.840391;-0.541980;0.000000;,
  0.000000;-0.541981;-0.840391;,
  0.707042;-0.000006;-0.707171;,
  0.000000;0.541910;-0.840437;,
  -0.707107;-0.000006;-0.707106;,
  0.840405;0.541959;0.000000;,
  0.000000;0.541909;0.840437;,
  0.000000;-0.000005;-1.000000;,
  0.000000;0.839339;-0.543608;,
  0.000000;-0.000005;1.000000;,
  0.000000;-0.839418;0.543487;,
  1.000000;-0.000005;0.000000;,
  -1.000000;-0.000005;0.000000;,
  0.000000;0.839339;0.543608;,
  0.000000;-0.839418;-0.543486;;
  24;
  4;0,17,20,14;,
  4;14,20,15,1;,
  4;20,16,3,15;,
  4;17,2,16,20;,
  4;2,8,21,16;,
  4;16,21,18,3;,
  4;26,19,5,18;,
  4;8,4,19,26;,
  4;4,11,22,19;,
  4;19,22,9,5;,
  4;22,10,7,9;,
  4;11,6,10,22;,
  4;6,13,23,10;,
  4;10,23,12,7;,
  4;27,14,1,12;,
  4;13,0,14,27;,
  4;1,15,24,12;,
  4;12,24,9,7;,
  4;24,18,5,9;,
  4;15,3,18,24;,
  4;6,11,25,13;,
  4;13,25,17,0;,
  4;25,8,2,17;,
  4;11,4,8,25;;
 }
 MeshTextureCoords {
  39;
  0.375000;0.000000;,
  0.375000;0.125000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.125000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.125000;0.250000;;
 }
}
