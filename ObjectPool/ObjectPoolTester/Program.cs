using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using ObjectPool;

namespace ObjectPoolTester
{
    class Program
    {
        public class MyClass : PooledObject
        {

        }

        static void MyTest()
        {
            var pool = new ObjectPool<MyClass>(0, 2);
            {
                var obj = pool.GetObject();
                obj.Dispose();
                obj = null;
                GC.Collect();
            }
        }
        
        static void Main(string[] args)
        {
            MyTest();            
        }

        static void PoolTest()
        {
            // Creating a pool with minimum size of 5 and maximum size of 25, using custom Factory method to create and instance of ExpensiveResource
            ObjectPool<ExpensiveResource> pool = new ObjectPool<ExpensiveResource>(5, 25, () => new ExpensiveResource(/* resource specific initialization */));

            using (ExpensiveResource resource = pool.GetObject())
            {
                // Using the resource
                // ...

            } // Exiting the using scope will return the object back to the pool


            // Creating a pool with wrapper object for managing external resources
            ObjectPool<PooledObjectWrapper<ExternalExpensiveResource>> newPool = new ObjectPool<PooledObjectWrapper<ExternalExpensiveResource>>(() => new PooledObjectWrapper<ExternalExpensiveResource>(CreateNewResource()) { WrapperReleaseResourcesAction = (r) => ExternalResourceReleaseResource(r), WrapperResetStateAction = (r) => ExternalResourceResetState(r) });

            using (var wrapper = newPool.GetObject())
            {
                // wrapper.InternalResource.DoStuff()
            }
        }

        private static ExternalExpensiveResource CreateNewResource()
        {
            return new ExternalExpensiveResource();
        }

        public static void ExternalResourceResetState(ExternalExpensiveResource resource)
        {
            // External Resource reset state code
        }

        public static void ExternalResourceReleaseResource(ExternalExpensiveResource resource)
        {
            // External Resource release code
        }
    }

    public class ExpensiveResource : PooledObject
    {

        public ExpensiveResource()
        {
            // Initialize the resource if needed
        }

        protected override void OnReleaseResources()
        {
            // Override if the resource needs to be manually cleaned before the memory is reclaimed
        }

        protected override void OnResetState()
        {
            // Override if the resource needs resetting before it is getting back into the pool
        }
    }

    public class ExternalExpensiveResource
    {
    }
}
