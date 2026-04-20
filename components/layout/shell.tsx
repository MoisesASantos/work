"use client"

import { useEffect, useState } from "react"
import { usePathname } from "next/navigation"
import { useRouter } from "next/navigation"
import { Sidebar } from "@/components/layout/sidebar"
import { TopNav } from "@/components/layout/top-nav"
import { BottomNav } from "@/components/layout/bottom-nav"
import { EmergencyButton } from "@/components/layout/emergency-button"

const AUTH_KEY = "apothecary_auth"

export function Shell({ children }: { children: React.ReactNode }) {
  const pathname = usePathname()
  const router = useRouter()
  const [isAuthChecked, setIsAuthChecked] = useState(false)
  const [isAuthenticated, setIsAuthenticated] = useState(false)
  const isPublicRoute = pathname === "/" || pathname === "/landing" || pathname === "/login"

  useEffect(() => {
    if (isPublicRoute) {
      setIsAuthChecked(true)
      return
    }

    const authed = localStorage.getItem(AUTH_KEY) === "true"
    setIsAuthenticated(authed)
    setIsAuthChecked(true)

    if (!authed) {
      router.replace(`/login?redirect=${encodeURIComponent(pathname)}`)
    }
  }, [isPublicRoute, pathname, router])

  if (isPublicRoute) {
    return <main className="min-h-screen bg-background">{children}</main>
  }

  if (!isAuthChecked || !isAuthenticated) {
    return <main className="min-h-screen bg-background" />
  }

  return (
    <>
      <Sidebar />
      <TopNav />
      <main className="md:ml-64 pt-16 pb-24 md:pb-8 min-h-screen bg-background">
        {children}
      </main>
      <BottomNav />
      <EmergencyButton />
    </>
  )
}
