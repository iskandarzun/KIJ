var express = require('express')();
var router = express;//express.Router();
//var mongoose = require('mongoose');

var session = require('express-session');
var passport = require('passport'),
    LocalStrategy = require('passport-local').Strategy;

//var User = require('../models/user');
//var Node = require('../models/node');
//var Usage = require('../models/usage');

express.use(session({secret: 'secretdude', saveUninitialized: true,
                 resave: true}));
express.use(passport.initialize());
express.use(passport.session());

/*
passport.use(new LocalStrategy({
    usernameField: 'uname',
    passwordField: 'passwd'
  },function(username, password, done) {
  	User.findOne({username : username, password : password},function(err, user){
  		if(user){
			done(null, user);
		}
	  	else
	    	done(null, false);
	});
}));

passport.serializeUser(function(user, done) {
  done(null, user.id);
});

passport.deserializeUser(function(id, done) {
  User.findById(id, function(err, user) {
    done(err, user);
  });
});

// called in number 2 argument get
// registration using another function without passport
var authentication = function(req, res, done) 
{
  if(req.isAuthenticated())
  {
    //done();
  	done();
  }
  else
  {
  	res.redirect('/login');
    // redirect to error page ex -> res.redirect('error page');
  }
}
*/

// GET index page
router.get('/', function(req, res, next) {
  res.render('index');
});

// GET register page
router.get('/register', function(req, res, next) {
  res.render('register');
});

// GET login page
router.get('/login_page', function(req, res, next) {
  res.render('login_page');
});

// GET admin dashboard in page
router.get('/dashboardadmin' ,function(req, res, next) {
  res.render('dashboardadmin');
});

// GET dashboard in page 
router.get('/dashboard' ,function(req, res, next) {
  res.render('dashboard');
});

// GET dashboard in page 
router.get('/dashboardadmin' ,function(req, res, next) {
  res.render('dashboardadmin');
});

// GET create_cert in page 
router.get('/create_cert' ,function(req, res, next) {
  if(req.query.page == 'page1')
  {
    res.render('create_cert');
  }
  else
  if(req.query.page == 'page2')
  {
    res.render('create_cert2');
  }
  else
  if(req.query.page == 'page3')
  {
    res.render('create_cert3');
  }
  else
  {
    res.render('create_cert');
  }
});

// GET form in page 
router.get('/form' ,function(req, res, next) {
  res.render('form');
});

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 9b85bfd

// GET list_cert in page
router.get('/list_cert', function(req, res, next){
  res.render('list_cert');
});

// POST create_cert in page
router.post('/create_cert', function(req, res, next) {
  if(req.query.page == 'page1')
  {
    res.render('create_cert');
  }
  else
  if(req.query.page == 'page2')
  {
    res.render('create_cert2');
  }
  else
  if(req.query.page == 'page3')
  {
    res.render('create_cert3');
  }
  else
  {
    res.render('create_cert');
  }
});

//GET registration in page

<<<<<<< HEAD
>>>>>>> 9b85bfd... Fixing routes/index.js
=======
>>>>>>> 9b85bfd
/*
router.post('/authenticate',passport.authenticate('local', { successRedirect: '/dashboard',
	failureRedirect: '/login'})
);

router.post('/register', function(req,res){
	var user = User({
		firstname : req.body.firstname,
		lastname  : req.body.lastname,
		email     : req.body.email,
		username  : req.body.username,
		password  : req.body.password
	});
	user.save();
});
router.post('/node',function(req,res){

});

// GET register page 
router.get('/register', function(req, res, next) {
  res.render('register', { title: 'Express' });
});

router.post('/node',function(req, res, next){
	var node = Node({	cpu : req.body.cpu,
						ram : req.body.ram,
						url : req.body.url,
						status : 0,
						 
					});
});
router.get('/dashboard',function(req,res,next){
	res.render('dashboard');
})
*/

module.exports = router;
