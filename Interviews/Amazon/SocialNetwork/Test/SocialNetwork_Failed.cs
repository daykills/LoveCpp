using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Amazon
{
    class Customer
    {
        public Customer(int ID, string Name)
        {
            this.ID = ID;
            this.Name = Name;

            LikedMovies = new Dictionary<int, int>();
            WatchedMovies = new List<int>();
            Friends = new List<int>();
        }
        public int ID { get; set; }
        public string Name { get; set; }
        public Dictionary<int, int> LikedMovies { get; set; }    // key = value = movie.ID
        public List<int> WatchedMovies; // IDs of watched movies
        public List<int> Friends;   // IDs of Friends        
    }

    public class SocialNetwork : SocialMovies
    {
        SocialNetwork()
        { }

        //////////////////////////////////////////////
        // private fields
        //////////////////////////////////////////////
        private Dictionary<int, string> movies = new Dictionary<int, string>();  // hash-table for movies: id / title
        private Dictionary<int, Customer> customers = new Dictionary<int, Customer>(); // hash-table for customers
        //////////////////////////////////////////////
        // implement interfaces
        // Defines a movie ID to title mapping in the system
        public void addMovie(int movieId, string title)
        { 
            if(movies.ContainsKey(movieId))
            {
                Console.WriteLine("Failed to add: movie {0} already exists.", title);
                return;
            }
            movies.Add(movieId, title);
        }

        // Returns the title of the given movie
        public string lookupMovie(int movieId)
        {
            if (movies.ContainsKey(movieId))
                return movies[movieId];
            Console.WriteLine("Failed to find movie {0}.", movieId);
            return null;
        }

        // Defines a customer ID to name mapping in the system
        public void addCustomer(int customerId, string name)
        {
            if(customers.ContainsKey(customerId))
            {
                Console.WriteLine("Failed to add: customer {0} already exists.", name);
                return;
            }
            Customer customer = new Customer(customerId, name);
            customers.Add(customerId, customer);
        }

        // Returns the name of the given customer
        public string lookupCustomer(int customerId)
        {
            if (customers.ContainsKey(customerId))
            {
                return customers[customerId].Name;
            }
            Console.WriteLine("Failed to find customer {0}.", customerId);
            return null;            
        }

        // Record that a movie was "liked" by the given customer
        public void addLikedMovie(int customerId, int movieId)
        {
            if (customers.ContainsKey(customerId) && movies.ContainsKey(movieId))
            {
                customers[customerId].LikedMovies.Add(movieId, movieId);
            }
            else
                Console.WriteLine("customer/movie doesn't exist.");
        }

        // Associate two customers as being friends
        public void addFriend(int customerId1, int customerId2)
        {
            if (customers.ContainsKey(customerId1) && (customers.ContainsKey(customerId2)))
            {
                if(customers[customerId1].Friends.Contains(customerId2))
                {
                    customers[customerId1].Friends.Add(customerId2);
                    customers[customerId2].Friends.Add(customerId1);
                }
            }
            else
                Console.WriteLine("customer doesn't exist.");
        }

        // use depth-first
        private void GetFriendsInDistance(Customer customer, int maxDistance, ref List<int> friends)
        {
            if (maxDistance == 0) return;
            foreach(int ID in customer.Friends)
            {
                if (friends.Contains(ID)) continue; // to avoid duplicate friend in List
                friends.Add(ID);
                Customer friend = customers[ID];                
                GetFriendsInDistance(friend, maxDistance - 1, ref friends);
            }
        }

        // Returns the ID of the customer who has the most "likes" in common with the given
        // customer.  The returned customer must be reachable by at most <maxDistance> friend links.
        public int getSimilarCustomerInNetwork(int customerId, int maxDistance)
        {
            
            Customer customer = customers[customerId];
            // to store all the friendsin the maxDistance
            List<int> friends = new List<int>();

            // the complexity is about O(V), V is the total number of customers
            GetFriendsInDistance(customer, maxDistance, ref friends); // use depth-first search

            // key = customerID; value = common like count
            Dictionary<int, int> likeCnts = new Dictionary<int, int>();
            foreach(int id in friends)
            {
                Customer friend = customers[id];
                foreach(int movieID in customer.LikedMovies.Keys)
                {
                    if(friend.LikedMovies.ContainsKey(movieID))
                    {
                        if (likeCnts.ContainsKey(id))
                            likeCnts[id]++;
                        else
                            likeCnts.Add(id, 1);
                    }
                }
            }
            int maxCnt = 0;
            int bestFriend = -1;
            foreach(int id in likeCnts.Keys)
            {
                if (likeCnts[id] > maxCnt)
                {
                    maxCnt = likeCnts[id];
                    bestFriend = id;
                }
            }
            if (bestFriend == -1)    // no common likes between customer and friends
                return -1;
            return bestFriend;
        }

        // Returns the IDs of the <maximumResults> movies with the highest total number of "likes".  All movies
        // returned must have a "like" count >= the like count of every non-returned movie.
        public IEnumerable<int> getMostLikedMovies(int maximumResults)
        {
            // sorry, unfinished.
            return null;
        }
    }
}
