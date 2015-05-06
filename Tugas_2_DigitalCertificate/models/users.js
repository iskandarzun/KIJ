var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var usersSchema = new Schema({
	firstName : String,
	lastName : String,
	contactEmail : String,
	contactTelp : String,

	username : String,
	password : String,

	companyType : String
});

module.exports = mongoose.model('User', usersSchema);
