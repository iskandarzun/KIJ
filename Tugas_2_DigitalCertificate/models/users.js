var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var usersSchema = new Schema({
	orgName : String,
	address : String,
	city : String,
	state : String,
	zipCode : String,
	country : String,

	jobTitle : String,
	firstName : String,
	lastName : String,
	contactEmail : String,
	contactTelp : String,

	username : String,
	password : String,

	companyType : String
});

mongoose.model('users', usersSchema);
