"use client"

import { usePathname } from "next/navigation"
import { Sidebar } from "@/components/layout/sidebar"
import { TopNav } from "@/components/layout/top-nav"
import { BottomNav } from "@/components/layout/bottom-nav"
import { EmergencyButton } from "@/components/layout/emergency-button"

export function Shell({ children }: { children: React.ReactNode }) {
  const pathname = usePathname()
  const isIsolated = pathname === "/landing" || pathname === "/login"

  if (isIsolated) {
    return <main className="min-h-screen bg-background">{children}</main>
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
