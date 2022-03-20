fit = 1 / 2;
length = 41;
CubePoints = [
  [  0,  0,  0 ],  //0
  [ 3 - fit,  0,  0 ],  //1
  [ 4 - fit,  length,  0 ],  //2
  [  -1 + fit,  length,  0 ],  //3
  [  0,  0,  10 ],  //4
  [ 3 - fit,  0,  10 ],  //5
  [ 4 - fit,  length,  10 ],  //6
  [  -1 + fit,  length,  10 ]]; //7
  
CubeFaces = [
  [0,1,2,3],  // bottom
  [4,5,1,0],  // front
  [7,6,5,4],  // top
  [5,6,2,1],  // right
  [6,7,3,2],  // back
  [7,4,0,3]]; // left
  
  polyhedron( CubePoints, CubeFaces);