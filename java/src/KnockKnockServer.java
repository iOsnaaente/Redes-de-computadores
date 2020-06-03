import java.net.*;
import java.io.*;

public class KnockKnockServer {
    public static void main(String[] args) throws IOException {

        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(4444);
        } catch (IOException e) {
            System.err.println("Could not listen on port: 4444.");
            System.exit(1);
        }

        Socket clientSocket = null;
        
        try {
            clientSocket = serverSocket.accept();
            
        } catch (IOException e) {
            System.err.println("Accept failed.");
            System.exit(1);
        }

        PrintStream out = new PrintStream(
                            new BufferedOutputStream(clientSocket.getOutputStream(), 1024),
                            false);
        
        DataInputStream in = new DataInputStream(
                            new BufferedInputStream(
			        clientSocket.getInputStream()
                            )
                        );
        
        String inputLine, outputLine;
        KnockKnockProtocol kkp = new KnockKnockProtocol();

        outputLine = kkp.processInput(null);
        out.println(outputLine);
        out.flush();

        while ((inputLine = in.readLine()) != null) {
             outputLine = kkp.processInput(inputLine);
             out.println(outputLine);
             out.flush();
             if (outputLine.equals("Bye."))
                break;
        }
        out.close();
        in.close();
        clientSocket.close();
        serverSocket.close();
    }
}
