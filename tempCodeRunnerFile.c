order("ganesh","ganeshnagar","7966247891","chinese",agentroot,1,userroot,3,1,restaurantroot);
    order("ganesh","ganeshnagar","7966247891","chinese",agentroot,1,userroot,3,1,restaurantroot);
    order("aditya","ramnagar","7846247891","northindian",agentroot,2,userroot,2,2,restaurantroot);
    order("john","kasnagar","7846247891","southindian",agentroot,3,userroot,4,2,restaurantroot);
    order("smit","vijaynagar","7846247891","Italian",agentroot,4,userroot,5,2,restaurantroot);
    
    printliveorders();
    delivery(1,agentroot,100);
    printliveorders();
    
    cancelorder(2,agentroot);
    printliveorders();