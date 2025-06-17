all: ./a.out

compRun:
		g++ main.cpp ProductAndInventoryManagement.cpp registrationAndLoginSystem.cpp employeeManagement.cpp SupplierManagement.cpp customerManagement.cpp SalesAndBillingSystem.cpp -o r.out




run: clean compRun; ./r.out

clean:
		rm -f *.out
