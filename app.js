'use strict'


const ffi = require('ffi-napi');

// C library API

// Express App (Routes)
const express = require("express");
const app     = express();
const path    = require("path");
const fileUpload = require('express-fileupload');
const body1 = require('body-parser');
app.use(body1.json());
app.use(body1.urlencoded({ extended: true }));

app.use(fileUpload());
app.use(express.static(path.join(__dirname+'/uploads')));

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/public/index.html'));
});

// Send Style, do not change
app.get('/style.css',function(req,res){
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname+'/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js',function(req,res){
  fs.readFile(path.join(__dirname+'/public/index.js'), 'utf8', function(err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, {compact: true, controlFlowFlattening: true});
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function(req, res) {
  if(!req.files) {
    return res.status(400).send('No files were uploaded.');
  }
 
  let uploadFile = req.files.uploadFile;
 
  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function(err) {
    if(err) {
      return res.status(500).send(err);
    }

    res.redirect('/');
  });
});

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function(req , res){
  fs.stat('uploads/' + req.params.name, function(err, stat) {
    if(err == null) {
      res.sendFile(path.join(__dirname+'/uploads/' + req.params.name));
    } else {
      console.log('Error in file downloading route: '+err);
      res.send('');
    }
  });
});

//******************** Your code goes here ******************** 
app.get('/foldercontents',function(req,res){
  let fileInfo = [];
  fs.readdir('uploads',(err,files)=>{
    let sharedLib = ffi.Library('./libsvgparser', {
    
      // 'SVGtojavaS':['string',['string']],
      'listToJSON':['string',['string']],
      'titleString':['string',['string']],
      'descString':['string',['string']]
  
    });
    files.forEach( (file) => {
      if(path.extname(file)!= '.svg'){
        return;
      }
      let filePr = {};
      filePr.name = file;
      filePr.size = fs.statSync("uploads/" + file).size + "kb";
      // console.log(filePr);

      // let agampc = sharedLib.SVGtojavaS("uploads/"+file);
      // let parser = JSON.parse(agampc);
      
      let file69 = sharedLib.listToJSON("uploads/"+file);
      let SVGpanel = JSON.parse(file69);
      let Title = sharedLib.titleString("uploads/"+file);
      let desc = sharedLib.descString("uploads/"+file);

      // let TDpanel = JSON.parse(TD);

      // filePr.rects = parser.numRect;
      // filePr.circs = parser.numCirc;
      // filePr.paths = parser.numPaths;
      // filePr.grps = parser.numGroups;
      
      // console.log(SVGpanel);
      filePr.rects = SVGpanel.numRect;
      // console.log('rects');
      filePr.circs = SVGpanel.numCirc;
      // console.log('circ');
      filePr.paths = SVGpanel.numPaths;
      // console.log('path');
      filePr.grps = SVGpanel.numGroups;
      filePr.title = Title;
      filePr.desc = desc;
      
      // console.log('grps');
      filePr.rectList = SVGpanel.rects;
      filePr.circList = SVGpanel.circs;
      filePr.pathList = SVGpanel.paths;
      filePr.groupList = SVGpanel.groups; 

      filePr.rectAttr = SVGpanel.attrRect;
      filePr.circAttr =SVGpanel.attrCirc;
      filePr.pathAttr =SVGpanel.attrPath;
      filePr.groupAttr =SVGpanel.attrGrp;
      filePr.svgAttr = SVGpanel.svgattr;
      console.log(filePr);
      fileInfo.push(filePr);
    });
    console.log(fileInfo);
    res.send(fileInfo);
  });
  
})






app.post('/add-shape', function(req,res) {
  let sharedLib = ffi.Library('./libsvgparser', {    
    'createRect':['bool',['string', 'string']],
    'createCirc':['bool',['string', 'string']]
  });
  
  let jsonString = {};
  if(req.body.shapeselect1 === 'Rectangle') {
    jsonString.x = req.body.x;
    jsonString.y = req.body.y;
    jsonString.w = req.body.width;
    jsonString.h = req.body.height;
    sharedLib.createRect("uploads/" + req.body.file, JSON.stringify(jsonString));
  }
  else {
    jsonString.cx = req.body.cx;
    jsonString.cy = req.body.cy;
    jsonString.r = req.body.r;
    sharedLib.createCirc("uploads/" + req.body.file, JSON.stringify(jsonString));
  }

  res.redirect('/');
});
app.post('/scale-shapes', function (req,res) {
  let sharedLib = ffi.Library('./libsvgparser', {    
    'scaleShapes':['void',['string', 'float', 'float']]
  });

  sharedLib.scaleShapes("uploads/" + req.body.file, req.body.rect, req.body.circ)
  res.redirect('/');
});

//Sample endpoint
app.get('/endpoint1', function(req , res){
  let retStr = req.query.data1 + " " + req.query.data2;
 
  res.send(
    {
      somethingElse: retStr
    }
  );
});


app.listen(portNum);
console.log('Running app at localhost: ' + portNum);