import org.json.JSONArray;
import org.json.JSONObject;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

public class Main {



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
                .thenApply(Main::parse)
                .join();
    }

    public static String parse(String responseBody)
    {
        JSONArray movies = new JSONArray(responseBody);
        for (int i = 0; i < movies.length(); i++)
        {
            JSONObject movie = movies.getJSONObject(i);
            int id = movie.getInt("id");
            String title = movie.getString("title");
            int year = movie.getInt("year");
            int score = movie.getInt("score");
            String type = movie.getString("type");
            System.out.println(id + " " + title + " " + year + " " + score + " " + type);
        }
        return null;
    }
}
