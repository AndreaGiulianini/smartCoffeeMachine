package seriale;

import java.io.Console;

public class start {

	public static void main(String[] args) throws Exception {
		SerialCommChannel channel = new SerialCommChannel(args[0],2000000);	
		
		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");	
		Console console = System.console();
		
		while (true){
			String msg = channel.receiveMsg();
			 System.out.println(msg);
			try {
				Integer.parseInt(msg);
				Thread.sleep(Integer.getInteger(msg)*1000);
				System.out.print("\033[H\033[2J");  
			    System.out.flush();
			} catch (NumberFormatException e) {};
			
			if(msg.contains("sugar:")) {
				System.out.println(msg.split(":")[1]);
			}
			if(msg.equals("No more coffee. Waiting for recharge")) {
				System.out.println(msg);
				while(console.readLine("refill coffee_pods?(y)") != "y" ) {}
			    channel.sendMsg("recharge");  
			    System.out.println("Coffee refilled: 10");    
			}
			
			if(msg.equals("Making a coffee")) { 
			    System.out.println(msg);    
			}
			if(msg.equals("The coffee is ready")) { 
			    System.out.println(msg);    
			}
			if(msg.equals("Welcome!")) { 
			    System.out.println(msg);    
			}
		}
	}

}
