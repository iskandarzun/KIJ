var express = require('express');
var https = require('https');
var pem = require('pem');
var fs = require('fs');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var flash = require('connect-flash');
var port = 9000;
var https_port = 9443;

var routes = require('./routes/index');
//var users = require('./routes/users');

var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/certitrust');

pem.createCertificate({days: 1, selfSigned: true}, function(err, keys) {
      var app = express();
      // view engine setup
      app.set('views', path.join(__dirname, 'views'));
      app.set('view engine', 'ejs');
      app.use('/public', express.static('public'));
      app.use(flash());

      // uncomment after placing your favicon in /public
      //app.use(favicon(__dirname + '/public/favicon.ico'));
      app.use(logger('dev'));
      app.use(bodyParser.json());
      app.use(bodyParser.urlencoded({ extended: false }));
      app.use(cookieParser());
      app.use(express.static(path.join(__dirname, 'public')));

      app.use('/', routes);
      //app.use('/users', users);
      // catch 404 and forward to error handler
      app.use(function(req, res, next) {
        var err = new Error('Not Found');
        err.status = 404;
        next(err);
      });

      // error handlers

      // development error handler
      // will print stacktrace
      if (app.get('env') === 'development') {
        app.use(function(err, req, res, next) {
          res.status(err.status || 500);
          if(err.status == undefined) err.status = 'Implementation Error';
          res.render('error', {
            message: err.message,
            error: err,
            status: err.status
          });
        });
      }

      // production error handler
      // no stacktraces leaked to user
      app.use(function(err, req, res, next) {
        res.status(err.status || 500);
        res.render('error', {
          message: err.message,
          error: {},
          status: err.status
        });
      });
      app.listen(port);
      var privateKey = fs.readFileSync('./ca.key', 'utf8');
      var certificate = fs.readFileSync('./ca.crt', 'utf8');
      var credentials = {key: privateKey, cert: certificate};
      https.createServer(credentials, app).listen(https_port);
      console.log('Http Listening on port : %d', port);
      console.log('Https Listening on port : %d', https_port);
      module.exports = app;
});

