var SerialManager = require('./lib/serialmanager.js');


describe("Customers", function(){
  it("retrieves by email", function(done){
    customer.findByEmail('test@test.com', function(doc){
      doc.email.should.equal('test@test.com');
      done();
    });
  });
});