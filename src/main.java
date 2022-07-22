import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

public class main {
    

    
    public static void main(String[] args) {
            HttpClient client = HttpClient.newHttpClient();
            HttpRequest request = HttpRequest.newBuilder()
                    .uri(URI.create("https://mdblist.p.rapidapi.com/?s=jaws"))
                    .header("X-RapidAPI-Key", "cee54a15cdmsh111590b419bfebcp182fd4jsnf2c5965ba2dc")
                    .header("X-RapidAPI-Host", "mdblist.p.rapidapi.com")
                    .method("GET", HttpRequest.BodyPublishers.noBody())
                    .build();
            client.sendAsync(request, HttpResponse.BodyHandlers.ofString())
                    .thenApply(HttpResponse::body)
                    .thenAccept(System.out::println)
                    .join();
    }

    public static String parse(String responseBody)
}
