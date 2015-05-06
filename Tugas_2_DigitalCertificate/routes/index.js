var express = require('express')();
var router = express;//express.Router();
var mongoose = require('mongoose');
var flash = require('connect-flash');

var session = require('express-session');
var passport = require('passport'),
    LocalStrategy = require('passport-local').Strategy;

var User = require('../models/users');
var Cert = require('../models/cert');

express.use(session({secret: 'secretdude', saveUninitialized: true,
                 resave: true}));
express.use(passport.initialize());
express.use(passport.session());
express.use(flash());

passport.use(new LocalStrategy({
    usernameField: 'username',
    passwordField: 'password'
  },function(username, password, done) {
  	User.findOne({username : username, password : password}, function(err, user){
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

/*
User.findOne({username: "feeljay"}, function(err, user){
      if(user){
      console.log('user : %s', user.password);
    }
      else
        console.log('nope');
  });
*/
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
  	res.redirect('/login_page');
    req.flash();
    // redirect to error page ex -> res.redirect('error page');
  }
}

var in_session = function(req, res, done) 
{
  if(req.isAuthenticated())
  {
    res.redirect('/dashboard');
  }
  else
  {
    done();
  }
}


// GET index page
router.get('/', in_session, function(req, res, next) {
  res.render('index');
});

// GET about page
router.get('/about', in_session, function(req, res, next) {
  res.render('about');
});

// GET feature page
router.get('/feature', in_session, function(req, res, next) {
  res.render('feature');
});

// GET register page
router.get('/register', in_session, function(req, res, next) {
  res.render('register');
});

// GET about page
router.get('/about', in_session, function(req, res, next) {
  res.render('about');
});

// GET login page
router.get('/login_page', in_session, function(req, res, next) {
  res.render('login_page');
});

// GET admin dashboard in page
router.get('/dashboardadmin' ,function(req, res, next) {
  res.render('dashboardadmin');
});

// GET dashboard in page 
router.get('/dashboard', authentication ,function(req, res, next) {
  res.render('dashboard');
});

// GET dashboard in page 
router.get('/dashboardadmin' ,function(req, res, next) {
  res.render('dashboardadmin');
});

// GET create_cert in page 
router.get('/create_cert', authentication, function(req, res, next) {
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

// GET list_cert in page
router.get('/list_cert', function(req, res, next){
  res.render('list_cert');
});

// GET logout in page
router.get('/logout', function(req, res, next) {
  req.logout();
  res.redirect('/');
});

//POST authenticate in page
router.post('/authenticate', passport.authenticate('local', { successRedirect: '/dashboard',
  failureRedirect: '/login_page', 
  failureFlash: "Invalid username or password"})
);

// POST create_cert in page
router.post('/create_cert', authentication, function(req, res, next) {
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
