var express = require('express')();
var router = express;//express.Router();
var mongoose = require('mongoose');
var flash = require('connect-flash');
var pem = require('pem');
var fs = require('fs');
var sys = require('sys')
var exec = require('child_process').execSync;
function puts(error, stdout, stderr) { sys.puts(stdout) }

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
  var listdir = fs.readdirSync('./public/users/' + req.user.username + "/");
  res.render('dashboard', {listdir: listdir});
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

// GET download in page 
router.get('/download', authentication, function(req, res, next) {
  var file = './public/users/' + req.user.username + '/' + req.query.name; 
  res.download(file);
});

// GET download in page 
router.get('/remove', authentication, function(req, res, next) {
  var file = './public/users/' + req.user.username + '/' + req.query.name; 
  fs.unlink(file);
  res.redirect('/dashboard');
});

// GET ca_cert in page 
router.get('/ca_cert', in_session, function(req, res, next) {
  var file = './ca.crt'; 
  res.download(file);
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

// POST register_user in page
router.post('/register', in_session ,function(req, res, next) {
  if(req.body.password == req.body.con_password)
  {
    var user = User({
      firstName: req.body.cp_fname,
      lastName: req.body.cp_lname,
      contactEmail: req.body.cp_email,
      contactTelp: req.body.cp_telephone,

      username: req.body.username,
      password: req.body.password,
      companyType: req.body.company
    })
    user.save();
    if (!fs.existsSync("./public/users/" + req.body.username)){
    fs.mkdirSync("./public/users/" + req.body.username);}
    res.redirect('/login_page');
  }
  else
  {
    res.redirect('/register');
  }
})

// POST create_cert in page
router.post('/create_cert', authentication, function(req, res, next) {
  if(req.query.page == 'page1')
  {
    req.session.destroy();
    res.render('create_cert');
  }
  else
  if(req.query.page == 'page2')
  {
    req.session.csr = req.body.csr;
    req.session.server_software = req.body.server_software;
    req.session.hash_algorithm = req.body.hash_algorithm;
    res.render('create_cert2');
  }
  else
  if(req.query.page == 'page3')
  {
    req.session.email = req.body.email;
    res.render('create_cert3');
  }
  else
  {
    req.session.destroy();
    res.render('create_cert');
  }
});

// POST generate_cert in page
router.post('/generate_cert', authentication, function(req, res, next) {
  var certificate_name = req.body.certificate_name;
  var days = req.body.days;
  /*
  var company = req.body.company_name;
  var dept = req.body.dept;
  var address = req.body.address;
  var city = req.body.city;
  var country = req.body.country
  */
  var privateKey = fs.readFileSync('./ca.key', 'utf8');
  var ca_crt = fs.readFileSync('./ca.crt', 'utf8');
  //console.log('generate\n');
  var dirpath = "./public/users/" + req.user.username + "/";
  fs.writeFileSync(dirpath + certificate_name + ".csr", req.session.csr)
  var command = "openssl x509 -req -in " + dirpath + certificate_name + ".csr -out " + dirpath + certificate_name + ".crt -CA ./ca.crt -CAkey ./ca.key -CAcreateserial -days "+ days;
  exec(command, puts);
  console.log(command);
  fs.unlink(dirpath + certificate_name + ".csr");

  //console.log('finish\n');
  
  /*
  var new_cert = pem.createCertificate({
    csr: req.session.csr,
    serviceKey: privateKey,
    serviceCertificate: ca_crt,
    selfSigned: false,
    serial: ,
    days: days
  }, function(err, keys) {
    //console.log(keys);
    fs.writeFileSync("./public/users/" + req.user.username + "/" + certificate_name + ".crt", keys.certificate);
    */
    res.redirect('/dashboard');
  //})
});

module.exports = router;
