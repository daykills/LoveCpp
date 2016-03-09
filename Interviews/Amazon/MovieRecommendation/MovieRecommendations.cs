using System;
using System.Collections.Generic;
 
namespace MyCollections
{
    public class Movie {
        private readonly int movieId;
        private readonly float rating;
        private List<Movie> similarMovies; // Similarity is bidirectional
 
        public Movie(int movieId, float rating) {
            this.movieId = movieId;
            this.rating = rating;
            similarMovies = new List<Movie>();
        }
 
        public int getId() {
            return movieId;
        }
 
        public float getRating() {
            return rating;
        }
 
        public void addSimilarMovie(Movie movie) {
            similarMovies.Add(movie);
            movie.similarMovies.Add(this);
        }
 
        public List<Movie> getSimilarMovies() {
            return similarMovies;
        }
 
        /*
         * Implement a function to return top rated movies in the network of movies 
         * reachable from the current movie
         * eg:            A(Rating 1.2)
         *               /   \
         *            B(2.4)  C(3.6)
         *              \     /
         *               D(4.8)
         * In the above example edges represent similarity and the number is rating.
         * getMovieRecommendations(A,2)should return C and D (sorting order doesn't matter so it can also return D and C)
         * getMovieRecommendations(A,4) should return A, B, C, D (it can also return these in any order eg: B,C,D,A)
         * getMovieRecommendations(A,1) should return D. Note distance from A to D doesn't matter, 
         *                            return the highest  rated.
         *     
         *     @param movie
         *     @param numTopRatedSimilarMovies 
         *                      number of movies we want to return
         *     @return List of top rated similar movies
         */
        public static IList<Movie> getMovieRecommendations(Movie movie, int numTopRatedSimilarMovies) {
            // Implement me
            return null;
        }
    }
}

