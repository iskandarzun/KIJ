var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var certSchema = new Schema({
	certificate : String,
	user : Schema.ObjectId
});

module.exports = mongoose.model('Cert', certSchema);
