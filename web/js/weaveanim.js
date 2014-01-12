var totalWidth = 1100;
var openWidth = 600;
var height = 100;
var speed = 1;
var rate = 2;
var prox = 40;
var numpoints = 8;
var cone = 10; // 1 px freedom after cone px
var strings = [{color: '#FF8000'}, {color: '#FF0080'}, {color: '#80FF00'},
  {color: '#00FF80'}, {color: '#8000FF'}, {color: '#0080FF'}];
var warpDivision = 10;

var weaveLength = 0;

function init() {
  for (var ss in strings) {
    var endy = (parseFloat(ss) + .5) * height / 6;

    var points = [];
    for (var ii = 0; ii < numpoints; ii++)
      points.push({x: ii * openWidth / numpoints, y: endy});
    strings[ss].points = points;
  }
  draw();
}

function draw() {
  var canvas = document.getElementById("canvas");  
  if (canvas.getContext) {  
    var ctx = canvas.getContext("2d"); 

    ctx.clearRect(0, 0, totalWidth, height);

    ctx.lineWidth = 4;
    ctx.beginPath();
    ctx.strokeStyle = "#000000";
    ctx.moveTo(openWidth, 0);
    ctx.lineTo(openWidth, height);
    ctx.stroke();

    ctx.lineWidth = 6;
    // Draw warp under
    ctx.beginPath();
    for (xx = weaveLength; xx > 0; xx -= 2*warpDivision) {
      ctx.strokeStyle = "#707070";

      ctx.moveTo(openWidth + xx, 0);
      ctx.lineTo(openWidth + xx, height);
    }
    ctx.stroke();

      ctx.lineWidth = 8;
    for (var ss in strings) {
      ctx.beginPath();

      ctx.strokeStyle = strings[ss].color;
      var points = strings[ss].points;
      var endy = (parseFloat(ss) + .5) * height / 6;

      if (points[0].x > 0)
        ctx.moveTo(0, points[0].y);
      else
        ctx.moveTo(points[0].x, points[0].y);

      for (var ii = 1; ii < numpoints - 1; ii += 2)
        ctx.bezierCurveTo(points[ii].x, points[ii].y, points[ii+1].x,
          points[ii+1].y, (points[ii+1].x + points[ii+2].x)/2, (points[ii+1].y + points[ii+2].y)/2);

      /*For debugging:
      {
        ctx.moveTo(points[ii-1].x, points[ii-1].y);
        ctx.lineTo(points[ii].x, points[ii].y);
        ctx.moveTo(points[ii+1].x, points[ii+1].y);
        ctx.lineTo((points[ii+1].x + points[ii+2].x)/2, (points[ii+1].y + points[ii+2].y)/2);
      }*/

      ctx.bezierCurveTo(points[numpoints-1].x, points[numpoints-1].y, (openWidth + points[numpoints-1].x)/2,
        endy, openWidth, endy);

      var xmove_from = (points[0].x < 0 ? 0 : 2);
      for (var ii = 0; ii < numpoints; ii++) {
        if (ii > 0 && ii >= xmove_from && ii < numpoints - 1) {
          if (points[ii].x - points[ii-1].x < prox)
            points[ii].x += rate*Math.random();
          else if (points[ii+1].x - points[ii].x < prox)
            points[ii].x -= rate*Math.random();
          else
            points[ii].x += 2*rate*(Math.random() - .5);
        }

        points[ii].y = Math.min(Math.max(points[ii].y + 2*rate*(Math.random() - .5),
            endy - (openWidth - points[2*Math.floor(ii/2)+1].x)/cone),
          endy + (openWidth - points[2*Math.floor(ii/2)+1].x)/cone);
      }

      // move everything forward
      for (var ii = xmove_from; ii < numpoints; ii++)
        points[ii].x += speed;

      if (points[numpoints-1].x > openWidth) {
        // Move all the middles forward two places
        for (var ii = numpoints-1; ii >= 3; ii--)
          points[ii] = points[ii-2];
        points[0].x = -2.5 * prox;
        points[1] = {x: -1.5 * prox, y: points[0].y};
        points[2] = {x: -points[3].x, y: points[0].y - (points[3].y - points[0].y)};
      }

      ctx.lineTo(openWidth + weaveLength, endy);

      strings[ss].points = points;
      ctx.stroke();
    }

    // Draw warp over
    ctx.lineWidth = 6;
    ctx.beginPath();
    for (xx = weaveLength - warpDivision; xx > 0; xx -= 2*warpDivision) {
      ctx.strokeStyle = "#909090";

      ctx.moveTo(openWidth + xx, 0);
      ctx.lineTo(openWidth + xx, height);
    }
    ctx.stroke();

    if (weaveLength < totalWidth + warpDivision * 2)
      weaveLength++;
    else
      weaveLength -= warpDivision * 2;

    setTimeout(function() { draw(); }, 100);
  }  
}
