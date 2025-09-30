FROM scratch
WORKDIR /app
COPY build/dnsplay .
CMD ["./dnsplay"]
