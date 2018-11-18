package seriale;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class start {

	public static void main(String[] args) throws Exception {
		SerialCommChannel channel = new SerialCommChannel( args[0], 2000000 );	
		
		System.out.print( "\033[H\033[2J" );  
	    System.out.flush();
		
		/* in this part of code you need to reboot your arduino */
		System.out.println( "Waiting Arduino for rebooting..." );		
		Thread.sleep( 4000 );
		System.out.println( "Ready." );
		
		while (true){
			String msg = channel.receiveMsg();
			try {
				msg = msg.substring( 0, msg.length() - 3 ); // remove new line
				
				try {
					// if the string is a number, so it represent the delay before remove the "Get coffee msg"
					int delay = Integer.parseInt( msg );
					Thread.sleep( delay * 1000 );
				} catch (NumberFormatException e) {};
				
				if( msg.contains( "Sugar:" ) ) {
					System.out.println( msg );
				}
				
				if( msg.equals( "Welcome!" ) || msg.equals( "The coffee is ready" ) || msg.equals( "Making a coffee" )  ) { 
				    System.out.println( msg );    
				}
				
				if ( msg.equals( "Coffee taken" ) || msg.equals( "No more coffee. Waiting for recharge" ) ) {
					// Coffee has been taken. The next command should clear terminal
					System.out.print( "\033[H\033[2J" );  
				    System.out.flush();
				}
				
				if( msg.equals( "No more coffee. Waiting for recharge" ) ) {
					System.out.println( msg );
					String s = "";
					do {
						try {
							s = ( new BufferedReader( new InputStreamReader( System.in ) ) ).readLine();
						} catch( Exception e ) {};
					} while( !s.equals("y") );
				    channel.sendMsg( "recharge" );  
				    System.out.println( "Coffee refilled: 10" );    
				}
			} catch( StringIndexOutOfBoundsException e ) {
				System.out.print( "msg out of bound. " );
				System.out.println( msg );
			}
		}
	}
}
