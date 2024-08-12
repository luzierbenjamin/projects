// Interpolationanimation.js By Benjamin Luzier
// Vertex shader program
var VSHADER_SOURCE =
  'attribute vec4 a_Position;\n' +
  'attribute vec4 a_Normal;\n' +
  'uniform mat4 u_MvpMatrix;\n' +
  'uniform mat4 u_NormalMatrix;\n' +
  'uniform vec3 u_LightDirection;\n' +
  'uniform float u_Rotation;\n' + // New uniform for the rotation angle
  'varying vec4 v_Color;\n' + //interpolation variable
  'void main() {\n' +
  'gl_Position = u_MvpMatrix * a_Position;\n' +
  'vec4 normal = u_NormalMatrix * a_Normal;\n' +
  'float nDotL = max(dot(u_LightDirection, normalize(normal.xyz)), 0.0);\n' +
  'float rotatedX = a_Position.x * cos(-u_Rotation) - a_Position.z * sin(-u_Rotation);\n' + // Calculate the rotated X position, u_rotation is negative to interpolate as it passes the Y-axis
  'vec4 color1 = vec4(0.0, 0.0, 1.0, 1.0);\n' + //blue
  'vec4 color2 = vec4(1.0, 0.0, 0.0, 1.0);\n' + //red
  'float t = smoothstep(-1.0, 1.0, rotatedX);\n' + // Generate a gradient from -1 to 1
  'vec4 color = mix(color1, color2, t); \n' + // Interpolate between the two colors
  'v_Color = vec4(color.xyz * nDotL, a_Position.w);\n' + //Multiplies the interpolated color by the intensity of light hitting the surface
  '}\n';

// Fragment shader program
var FSHADER_SOURCE =
  '#ifdef GL_ES\n' +
  'precision mediump float;\n' +
  '#endif\n' +
  'varying vec4 v_Color;\n' +
  'void main() {\n' +
  '  gl_FragColor = v_Color;\n' + //set the frag color to the calculated vertex color
  '}\n';

function main() { //main code for the canvas It is called by the html onload and it does the main processing to get the webgl content ready and sets up the shaders. It also processes the array and draws it. It calls the tick and gets the model_matrix elements ready. Its end result is to display the canvas and the colored cubes rotating and interpolating.
  // Retrieve <canvas> element
  var canvas = document.getElementById('webgl');

  // Get the rendering context for WebGL
  var gl = getWebGLContext(canvas);
  if (!gl) {
    console.log('Failed to get the rendering context for WebGL');
    return;
  }

  // Initialize shaders
  if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
    console.log('Failed to intialize shaders.');
    return;
  }

  // 
  var n = initVertexBuffers(gl);
  if (n < 0) {
    console.log('Failed to set the vertex information');
    return;
  }

  // Set the clear color and enable the depth test
  gl.clearColor(0, 0, 0, 1);
  gl.enable(gl.DEPTH_TEST);

  // Get the storage locations of uniform variables and so on
  var u_MvpMatrix = gl.getUniformLocation(gl.program, 'u_MvpMatrix');
  var u_NormalMatrix = gl.getUniformLocation(gl.program, 'u_NormalMatrix');
  var u_LightDirection = gl.getUniformLocation(gl.program, 'u_LightDirection');
  var u_Rotation = gl.getUniformLocation(gl.program, 'u_Rotation'); 
  if (!u_MvpMatrix || !u_NormalMatrix || !u_LightDirection || !u_Rotation) { 
    console.log('Failed to get the storage location');
    return;
  }

  var vpMatrix = new Matrix4();   // View projection matrix
  // Calculate the view projection matrix
  vpMatrix.setPerspective(30, canvas.width/canvas.height, 1, 100);
  vpMatrix.lookAt(3, 3, 7, 0, 0, 0, 0, 1, 0);
  // Set the light direction (in the world coordinate)
  var lightDirection = new Vector3([0.5, 3.0, 4.0]);
  lightDirection.normalize();     // Normalize
  gl.uniform3fv(u_LightDirection, lightDirection.elements);
  
  var currentAngle = 0.0;  // Current rotation angle
  var modelMatrix = new Matrix4();  // Model matrix
  var mvpMatrix = new Matrix4();    // Model view projection matrix
  var normalMatrix = new Matrix4(); // Transformation matrix for normals

  


  var tick = function() { //This function is called by main. Its purpose is to update the rotation angle and interpolate the cubes as needed. It processes this information and its end result is the new position of the cubes on the canvas.
    currentAngle = animate(currentAngle);  // Update the rotation angle
    
    // Pass the rotation angle to the shader
    var radian = Math.PI * currentAngle / 180.0; //Radian added to be sent and to help in the interpolation process
    gl.uniform1f(u_Rotation, radian);

    // Calculate the model matrix
    modelMatrix.setRotate(currentAngle, 0, 1, 0); // Rotate around the y-axis
    
        

    mvpMatrix.set(vpMatrix).multiply(modelMatrix);
    gl.uniformMatrix4fv(u_MvpMatrix, false, mvpMatrix.elements);

    // Pass the matrix to transform the normal based on the model matrix to u_NormalMatrix
    normalMatrix.setInverseOf(modelMatrix);
    normalMatrix.transpose();
    gl.uniformMatrix4fv(u_NormalMatrix, false, normalMatrix.elements);

    // Clear color and depth buffer
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // Draw the cube
    gl.drawElements(gl.TRIANGLES, n, gl.UNSIGNED_BYTE, 0);

    requestAnimationFrame(tick, canvas); // Request that the browser ?calls tick
  };
  tick();
}



function initVertexBuffers(gl) { //Function is called by main. Its input value is the gl. It processes the vertecies of the cubes, normals of the cubes, indices of the cubes it creates the buffer object, and then it binds the buffer object to the target. Its end result is returning the processed information to main to create the cubes on the canvas, by returning indicies.length.
  // Create a cube, all 3 cubes follow the same vertices
  //    v6----- v5
  //   /|      /|
  //  v1------v0|
  //  | |     | |
  //  | |v7---|-|v4
  //  |/      |/
  //  v2------v3
  // Coordinates
var vertices = new Float32Array([
    // First cube, is on the right side to start
    1.875, 0.25, 0.25,   1.375, 0.25, 0.25,   1.375,-0.25, 0.25,    1.875,-0.25, 0.25, // v0-v1-v2-v3 front
    1.875, 0.25, 0.25,    1.875,-0.25, 0.25,    1.875,-0.25,-0.25,    1.875, 0.25,-0.25, // v0-v3-v4-v5 right
    1.875, 0.25, 0.25,    1.875, 0.25,-0.25,   1.375, 0.25,-0.25,   1.375, 0.25, 0.25, // v0-v5-v6-v1 up
    1.375, 0.25, 0.25,   1.375, 0.25,-0.25,   1.375,-0.25,-0.25,   1.375,-0.25, 0.25, // v1-v6-v7-v2 left
    1.375,-0.25,-0.25,    1.875,-0.25,-0.25,    1.875,-0.25, 0.25,   1.375,-0.25, 0.25, // v7-v4-v3-v2 down
    1.875,-0.25,-0.25,   1.375,-0.25,-0.25,   1.375, 0.25,-0.25,    1.875, 0.25,-0.25,  // v4-v7-v6-v5 back
    // Second cube (adjusted for equal distance along x-axis), is on the left side to start
    -1.875, 0.25, 0.25,   -1.375, 0.25, 0.25,   -1.375,-0.25, 0.25,    -1.875,-0.25, 0.25, // v0-v1-v2-v3 front
    -1.875, 0.25, 0.25,    -1.875,-0.25, 0.25,    -1.875,-0.25,-0.25,    -1.875, 0.25,-0.25, // v0-v3-v4-v5 right
    -1.875, 0.25, 0.25,    -1.875, 0.25,-0.25,   -1.375, 0.25,-0.25,   -1.375, 0.25, 0.25, // v0-v5-v6-v1 up
    -1.375, 0.25, 0.25,   -1.375, 0.25,-0.25,   -1.375,-0.25,-0.25,   -1.375,-0.25, 0.25, // v1-v6-v7-v2 left
    -1.375,-0.25,-0.25,    -1.875,-0.25,-0.25,    -1.875,-0.25, 0.25,   -1.375,-0.25, 0.25, // v7-v4-v3-v2 down
    -1.875,-0.25,-0.25,   -1.375,-0.25,-0.25,   -1.375, 0.25,-0.25,    -1.875, 0.25,-0.25,  // v4-v7-v6-v5 back
    //third cube, in the center
    0.25, 0.25, 0.25,   -0.25, 0.25, 0.25,   -0.25,-0.25, 0.25,    0.25,-0.25, 0.25, // v0-v1-v2-v3 front
    0.25, 0.25, 0.25,    0.25,-0.25, 0.25,    0.25,-0.25,-0.25,    0.25, 0.25,-0.25, // v0-v3-v4-v5 right
    0.25, 0.25, 0.25,    0.25, 0.25,-0.25,   -0.25, 0.25,-0.25,   -0.25, 0.25, 0.25, // v0-v5-v6-v1 up
    -0.25, 0.25, 0.25,  -0.25, 0.25,-0.25,  -0.25,-0.25,-0.25,  -0.25,-0.25, 0.25, // v1-v6-v7-v2 left
    -0.25,-0.25,-0.25,   0.25,-0.25,-0.25,   0.25,-0.25, 0.25,  -0.25,-0.25, 0.25, // v7-v4-v3-v2 down
    0.25,-0.25,-0.25,  -0.25,-0.25,-0.25,  -0.25, 0.25,-0.25,   0.25, 0.25,-0.25  // v4-v7-v6-v5 back
]);

  // Normal
  var normals = new Float32Array([
    0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,  // v0-v1-v2-v3 front
    1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,  // v0-v3-v4-v5 right
    0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,  // v0-v5-v6-v1 up
   -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  // v1-v6-v7-v2 left
    0.0,-1.0, 0.0,   0.0,-1.0, 0.0,   0.0,-1.0, 0.0,   0.0,-1.0, 0.0,  // v7-v4-v3-v2 down
    0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   0.0, 0.0,-1.0,  // v4-v7-v6-v5 back
    ///second cube left, right and left side normals are changed so that the cubes all have light effect the same way
    0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,  // v0-v1-v2-v3 front
    -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  // v0-v3-v4-v5 right
    0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,  // v0-v5-v6-v1 up
   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,  // v1-v6-v7-v2 left
    0.0,-1.0, 0.0,   0.0,-1.0, 0.0,   0.0,-1.0, 0.0,   0.0,-1.0, 0.0,  // v7-v4-v3-v2 down
    0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   0.0, 0.0,-1.0,  // v4-v7-v6-v5 back
    //third cube center
    0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,  // v0-v1-v2-v3 front
    1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,  // v0-v3-v4-v5 right
    0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,  // v0-v5-v6-v1 up
   -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  // v1-v6-v7-v2 left
    0.0,-1.0, 0.0,   0.0,-1.0, 0.0,   0.0,-1.0, 0.0,   0.0,-1.0, 0.0,  // v7-v4-v3-v2 down
    0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   0.0, 0.0,-1.0   // v4-v7-v6-v5 back
  ]);

  // Indices of the vertices
  var indices = new Uint8Array([
     0, 1, 2,   0, 2, 3,    // front
     4, 5, 6,   4, 6, 7,    // right
     8, 9,10,   8,10,11,    // up
    12,13,14,  12,14,15,    // left
    16,17,18,  16,18,19,    // down
    20,21,22,  20,22,23,    // back
    // second cube 
     24, 25, 26, 24, 26, 27, // front (cube 2)
     28, 29, 30, 28, 30, 31, // right (cube 2)
     32, 33, 34, 32, 34, 35, // up (cube 2)
     36, 37, 38, 36, 38, 39, // left (cube 2)
     40, 41, 42, 40, 42, 43, // down (cube 2)
     44, 45, 46, 44, 46, 47,  // back (cube 2)
     //third cube 
     48, 49, 50,   48, 50, 51, // Front face
    52, 53, 54,   52, 54, 55, // Right face
    56, 57, 58,   56, 58, 59, // Up face
    60, 61, 62,   60, 62, 63, // Left face
    64, 65, 66,   64, 66, 67, // Down face
    68, 69, 70,   68, 70, 71  // Back face
 ]);


 
  // Write the vertex property to buffers (coordinates, colors and normals)
  if (!initArrayBuffer(gl, 'a_Position', vertices, 3, gl.FLOAT)) return -1;
  //if (!initArrayBuffer(gl, 'a_Color', colors, 3, gl.FLOAT)) return -1;
  if (!initArrayBuffer(gl, 'a_Normal', normals, 3, gl.FLOAT)) return -1;

  // Unbind the buffer object
  gl.bindBuffer(gl.ARRAY_BUFFER, null);

  // Write the indices to the buffer object
  var indexBuffer = gl.createBuffer();
  if (!indexBuffer) {
    console.log('Failed to create the buffer object');
    return false;
  }
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW);

  return indices.length;
}

function initArrayBuffer(gl, attribute, data, num, type) { //Functions purpose is to initilize the vertex array buffer. It is called by main. It processes the initilization of the vertex from the parameters of gl, attribute, data, num, and type. Its end result is the initiization of the vertex array buffer
  // Create a buffer object
  var buffer = gl.createBuffer();
  if (!buffer) {
    console.log('Failed to create the buffer object');
    return false;
  }
  // Write date into the buffer object
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ARRAY_BUFFER, data, gl.STATIC_DRAW);
  // Assign the buffer object to the attribute variable
  var a_attribute = gl.getAttribLocation(gl.program, attribute);
  if (a_attribute < 0) {
    console.log('Failed to get the storage location of ' + attribute);
    return false;
  }
  gl.vertexAttribPointer(a_attribute, num, type, false, 0, 0);
  // Enable the assignment of the buffer object to the attribute variable
  gl.enableVertexAttribArray(a_attribute);

  return true;
}

// Rotation angle (degrees/second)
var ANGLE_STEP = 30.0;
// Last time that this function was called
var g_last = Date.now();
function animate(angle) { //This function is called by tick. It processes the time to properly process the animation. Its end result is returning the new angle without remainder. 
  // Calculate the elapsed time
  var now = Date.now();
  var elapsed = now - g_last;
  g_last = now;  
  // Update the current rotation angle (adjusted by the elapsed time)
  var newAngle = angle + (ANGLE_STEP * elapsed) / 1000.0;
  return newAngle %= 360;
}
