

var yuvRgbMatrix = [
    [1, 0, 1.13983],
    [1, -0.39465, -0.58060],
    [1, 2.03211, 0]
];

var studioSwing = [
    [66/256, 129/256, 25/256],
    [-38/256, -74/256, 112/256],
    [112/256, -94/256, -18/256]
]

function yuvRgb(arr /*[y,u,v]*/, matrix /*BT-601*/){    
    var m = matrix;

    var result = [];
    for(var i = 0; i < arr.length; i++){
        result[i] = 0;
        for(var j = 0; j < m[i].length; j++){
            result[i] += m[i][j]*arr[j];
        }
    }
    return result;
}

// yuvRgb([65,117,238], yuvRgbMatrix)
rgb = yuvRgb([255,0,0], studioSwing)
rgb
rgb.map((i, index)=>{ 
    if(index == 0) return i+16;
    return i+128;
})
rgb
